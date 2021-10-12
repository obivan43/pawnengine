#include "MainWindowImpl.h"
#include "PawnSystem/system/windows/SystemPC.h"
#include "PawnSystem/system/windows/InputManagerWindows.h"
#include "PawnUtils/utils/logger/Logger.h"

#include "gui/QtAdvancedDocking/docking/DockAreaWidget.h"

#include <QSettings>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QString>

#include <string>
#include <iomanip>

namespace editor {

	namespace impl {

		MainWindowImpl::MainWindowImpl(QApplication* application, QWidget* parent)
			: MainWindow(parent)
			, m_Application(application)
			, m_Output(nullptr)
			, m_Hierarchy(nullptr)
			, m_Inspector(nullptr)
			, m_EngineView(nullptr)
			, m_EngineManager(nullptr)
			, m_IsFreshStart(true)
			, m_IsCursorHidden(false) {
			setWindowTitle("Pawn Engine Editor");
			setWindowIcon(QIcon(":/pawn.png"));
			resize(EditorDefaultWidth, EditorDefaultHeight);

			m_FileMenu = menuBar()->addMenu("File");
			m_ViewMenu = menuBar()->addMenu("View");
			m_EngineMenu = menuBar()->addMenu("Engine");

			m_EngineView = EngineViewWidget::CreateImpl(this);
			m_Output = OutputWidget::CreateImpl(this);
			m_Inspector = InspectorWidget::CreateImpl(this);
			m_Hierarchy = HierarchyWidget::CreateImpl(this);

			ads::CDockManager::setConfigFlag(ads::CDockManager::OpaqueSplitterResize, true);
			ads::CDockManager::setConfigFlag(ads::CDockManager::XmlCompressionEnabled, false);
			ads::CDockManager::setConfigFlag(ads::CDockManager::FocusHighlighting, true);

			m_DockManager = new ads::CDockManager(this);

			ads::CDockWidget* EngineViewDockWidget = new ads::CDockWidget("Engine view");
			EngineViewDockWidget->setWidget(m_EngineView);
			m_EngineView->setMinimumSize(EngineViewWidth, EngineViewHeight);
			EngineViewDockWidget->setMinimumSize(EngineViewWidth, EngineViewHeight);

			ads::CDockWidget* OutputDockWidget = new ads::CDockWidget("Output");
			OutputDockWidget->setWidget(m_Output);

			ads::CDockWidget* InspectorDockWidget = new ads::CDockWidget("Inspector");
			InspectorDockWidget->setWidget(m_Inspector);

			ads::CDockWidget* HierarchyDockWidget = new ads::CDockWidget("Hierarchy");
			HierarchyDockWidget->setWidget(m_Hierarchy);

			EngineViewDockWidget->setObjectName("EngineViewDockWidget");
			OutputDockWidget->setObjectName("OutputDockWidget");
			InspectorDockWidget->setObjectName("InspectorDockWidget");
			HierarchyDockWidget->setObjectName("HierarchyDockWidget");

			QAction* openAction = new QAction("Open", this);
			openAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));

			QAction* saveAction = new QAction("Save", this);
			saveAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));

			m_FileMenu->addAction(openAction);
			m_FileMenu->addAction(saveAction);

			m_ViewMenu->addAction(EngineViewDockWidget->toggleViewAction());
			m_ViewMenu->addAction(OutputDockWidget->toggleViewAction());
			m_ViewMenu->addAction(InspectorDockWidget->toggleViewAction());
			m_ViewMenu->addAction(HierarchyDockWidget->toggleViewAction());

			QAction* startAction = new QAction("Start", this);
			startAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F5));

			QAction* pauseAction = new QAction("Pause", this);
			pauseAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F6));

			QAction* resetAction = new QAction("Reset", this);
			resetAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F7));

			m_EngineMenu->addAction(startAction);
			m_EngineMenu->addAction(pauseAction);
			m_EngineMenu->addAction(resetAction);

			ads::CDockAreaWidget* centralDockArea = m_DockManager->setCentralWidget(EngineViewDockWidget);
			centralDockArea->setAllowedAreas(ads::DockWidgetArea::OuterDockAreas);

			m_DockManager->addDockWidget(ads::BottomDockWidgetArea, OutputDockWidget, EngineViewDockWidget->dockAreaWidget());
			m_DockManager->addDockWidget(ads::RightDockWidgetArea, InspectorDockWidget, EngineViewDockWidget->dockAreaWidget());
			m_DockManager->addDockWidget(ads::BottomDockWidgetArea, HierarchyDockWidget, InspectorDockWidget->dockAreaWidget());

			InitConnections();
			RestoreSettings();

			InitEngine();

			m_EngineManager = new EngineManager(m_Engine.get());

			m_Hierarchy->SetEngineManager(m_EngineManager);

			QAction* showHideCursor = new QAction("Show/Hide cursor", this);
			showHideCursor->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_K));
			addAction(showHideCursor);

			connect(m_Inspector, SIGNAL(EntityMeshModfied(pawn::engine::GameEntity)), m_EngineManager, SLOT(OnEntityMeshModified(pawn::engine::GameEntity)));
			connect(startAction, SIGNAL(triggered()), this, SLOT(Start()));
			connect(pauseAction, SIGNAL(triggered()), this, SLOT(Pause()));
			connect(resetAction, SIGNAL(triggered()), this, SLOT(Reset()));
			connect(openAction, SIGNAL(triggered()), this, SLOT(Open()));
			connect(saveAction, SIGNAL(triggered()), this, SLOT(Save()));
			connect(showHideCursor, SIGNAL(triggered()), this, SLOT(ShowHideCursor()));
		}

		void MainWindowImpl::Start() {
			if (m_IsFreshStart) {
				m_Engine->SaveState("temp.pawn");
				m_IsFreshStart = false;
			}

			m_Engine->GetScriptEngine()->SetIsPaused(false);
			m_Hierarchy->setEnabled(false);
			m_Inspector->setEnabled(false);
			m_FileMenu->setEnabled(false);
		}

		void MainWindowImpl::Pause() {
			m_Engine->GetScriptEngine()->SetIsPaused(true);
		}

		void MainWindowImpl::Reset() {
			if (!m_IsFreshStart) {
				m_Engine->GetScriptEngine()->SetIsPaused(true);

				m_Engine->LoadState("temp.pawn");

				m_Hierarchy->setEnabled(true);
				m_Inspector->setEnabled(true);
				m_FileMenu->setEnabled(true);

				m_IsFreshStart = true;
			}
		}

		void MainWindowImpl::Open() {
			QString filter("All File (*.*) ;; Text File (*.txt) ;; Pawn File (*.pawn)");
			QString fileName = QFileDialog::getOpenFileName(this, "Open a file", QDir::homePath(), filter);
			if (!fileName.isEmpty()) {
				m_Engine->LoadState(fileName.toLocal8Bit().constData());
				m_Hierarchy->RefreshPanel();
			}
		}

		void MainWindowImpl::Save() {
			QString filter("All File (*.*) ;; Text File (*.txt) ;; Pawn File (*.pawn)");
			QString fileName = QFileDialog::getSaveFileName(this, "Save a file", QDir::homePath(), filter);
			if (!fileName.isEmpty()) {
				m_Engine->SaveState(fileName.toLocal8Bit().constData());
			}
		}

		void MainWindowImpl::ShowHideCursor() {
			if (!m_IsCursorHidden) {
				QCursor cursor(Qt::BlankCursor);
				m_Application->setOverrideCursor(cursor);
				m_Application->changeOverrideCursor(cursor);
				m_IsCursorHidden = true;
#ifdef _WIN32
				HWND handle = m_EngineView->GetWindowsHandle();
				RECT rect;
				GetClientRect(handle, &rect);
				MapWindowPoints(handle, nullptr, reinterpret_cast<POINT*>(&rect), 2);
				ClipCursor(&rect);
#endif
			}
			else {
				m_Application->restoreOverrideCursor();
				m_IsCursorHidden = false;
#ifdef _WIN32
				ClipCursor(nullptr);
#endif
			}
		}

		void MainWindowImpl::closeEvent(QCloseEvent* event) {
			std::remove("temp.pawn");
			m_Engine->SetEngineRunning(false);

			QSettings settings("Shulzhenko corp", "Pawnengine");

			settings.setValue("geometry", saveGeometry());
			settings.setValue("windowState", saveState());

			settings.setValue("dockManagerGeometry", m_DockManager->saveGeometry());
			settings.setValue("dockManagerState", m_DockManager->saveState());

			QMainWindow::closeEvent(event);
		}

		void MainWindowImpl::RestoreSettings() {
			QSettings settings("Shulzhenko corp", "Pawnengine");
			restoreGeometry(settings.value("geometry").toByteArray());
			restoreState(settings.value("windowState").toByteArray());

			m_DockManager->restoreGeometry(settings.value("dockManagerGeometry").toByteArray());
			m_DockManager->restoreState(settings.value("dockManagerState").toByteArray());
		}

		void MainWindowImpl::InitEngine() {
			m_Engine.reset(new pawn::engine::Engine);

			SetGameEngineWindowHWND(m_EngineView->GetWindowsHandle());

			pawn::system::InputManagerWindows::RegisterMouse();
			pawn::system::InputManagerWindows::RegisterKeyboard();

			m_Engine->Init(GetGameEngineWindowHWND(), EngineViewWidth, EngineViewHeight);

			std::shared_ptr<pawn::engine::GameScene>& scene{ m_Engine->GetScene() };

			m_Engine->UploadMeshFromFile("res/assets/models/cube.obj");
			m_Engine->UploadMeshFromFile("res/assets/models/sphere.obj");
			m_Engine->UploadMeshFromFile("res/assets/models/cylinder.obj");
			m_Engine->UploadMeshFromFile("res/assets/models/cone.obj");
			m_Engine->UploadMeshFromFile("res/assets/models/torus.obj");

			m_Engine->UploadTextureFromFile("res/assets/textures/brick.jpg");

			pawn::engine::GameEntity camera{ scene->CreateEntity("camera") };
			pawn::engine::CameraComponent& cameraComponent{ camera.AddComponent<pawn::engine::CameraComponent>() };
			cameraComponent.IsActiveCamera = true;

			pawn::engine::TransformationComponent& transformation = camera.GetComponent<pawn::engine::TransformationComponent>();
			transformation.Position = glm::vec3(0.0f, 0.0f, 4.0f);

			camera.AddComponent<pawn::engine::ScriptComponent>("res/assets/scripts/Movement.lua");

			emit ActiveSceneChanged(scene);
		}

		void MainWindowImpl::InitConnections() {
			connect(
				this,
				SIGNAL(ActiveSceneChanged(std::shared_ptr<pawn::engine::GameScene>)),
				m_Hierarchy,
				SLOT(OnActiveSceneChanged(std::shared_ptr<pawn::engine::GameScene>))
			);

			connect(
				m_Hierarchy,
				SIGNAL(SelectedEntityChanged(pawn::engine::GameEntity)),
				m_Inspector,
				SLOT(OnSelectedEntityChanged(pawn::engine::GameEntity))
			);

			connect(
				m_Inspector,
				SIGNAL(EntityTagModified()),
				m_Hierarchy,
				SLOT(OnEntityTagModified())
			);
		}

	}

}
