#include "MainWindowImpl.h"
#include "PawnSystem/system/windows/SystemPC.h"
#include "PawnSystem/system/windows/InputManagerWindows.h"

#include "gui/QtAdvancedDocking/docking/DockAreaWidget.h"

#include <QSettings>
#include <string>
#include <QMenu>
#include <QMenuBar>

#include <iomanip>

namespace editor {

	namespace impl {

		MainWindowImpl::MainWindowImpl(QWidget* parent)
			: MainWindow(parent)
			, m_Output(nullptr)
			, m_Hierarchy(nullptr)
			, m_Inspector(nullptr)
			, m_EngineView(nullptr)
			, m_EngineManager(nullptr) {
			setWindowTitle("Pawn Engine Editor");
			setWindowIcon(QIcon(":/pawn.png"));
			resize(EditorDefaultWidth, EditorDefaultHeight);

			m_DockMenu = menuBar()->addMenu("View");

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

			m_DockMenu->addAction(EngineViewDockWidget->toggleViewAction());
			m_DockMenu->addAction(OutputDockWidget->toggleViewAction());
			m_DockMenu->addAction(InspectorDockWidget->toggleViewAction());
			m_DockMenu->addAction(HierarchyDockWidget->toggleViewAction());

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

			connect(m_Inspector, SIGNAL(EntityMeshModfied(pawn::engine::GameEntity)), m_EngineManager, SLOT(OnEntityMeshModified(pawn::engine::GameEntity)));
		}

		void MainWindowImpl::closeEvent(QCloseEvent* event) {
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
			m_Engine->GetScriptEngine()->SetIsPaused(false);

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

			camera.AddComponent<pawn::engine::ScriptComponent>("res/assets/scripts/Camera.lua");

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
