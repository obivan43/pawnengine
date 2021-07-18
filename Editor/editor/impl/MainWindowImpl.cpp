#include "MainWindowImpl.h"
#include "PawnSystem/system/windows/SystemPC.h"
#include "PawnSystem/system/windows/InputManagerWindows.h"

#include <QSettings>
#include <string>

namespace editor {

	namespace impl {

		MainWindowImpl::MainWindowImpl(QWidget* parent)
			: MainWindow(parent)
			, m_BottomPanel(nullptr)
			, m_LeftPanel(nullptr)
			, m_RightPanel(nullptr)
			, m_CentralWidget(nullptr)
			, m_EngineManager(nullptr) {
			setWindowTitle("Pawn Engine Editor");
			setWindowIcon(QIcon(":/pawn.png"));
			resize(EditorDefaultWidth, EditorDefaultHeight);

			m_CentralWidget = CentralWidget::CreateImpl(this);
			m_CentralWidget->setMinimumSize(EngineViewWidth, EngineViewHeight);
			setCentralWidget(m_CentralWidget);

			m_BottomPanel = BottomPanelWidget::CreateImpl(this);
			m_RightPanel = RightPanelWidget::CreateImpl(this);
			m_LeftPanel = LeftPanelWidget::CreateImpl(this);

			m_BottomPanel->setObjectName("Console");
			m_RightPanel->setObjectName("Inspector");
			m_LeftPanel->setObjectName("Scene Hierarchy");
			m_CentralWidget->setObjectName("Engine view");

			addDockWidget(Qt::BottomDockWidgetArea, m_BottomPanel);
			addDockWidget(Qt::RightDockWidgetArea, m_RightPanel);
			addDockWidget(Qt::LeftDockWidgetArea, m_LeftPanel);

			InitConnections();
			RestoreSettings();

			InitEngine();

			m_EngineManager = new EngineManager(m_Engine.get());
			connect(m_RightPanel, SIGNAL(EntityMeshModfied(pawn::engine::GameEntity)), m_EngineManager, SLOT(OnEntityMeshModified(pawn::engine::GameEntity)));
		}

		void MainWindowImpl::closeEvent(QCloseEvent* event) {
			Running = false;

			QSettings settings("Shulzhenko corp", "Pawnengine");
			settings.setValue("geometry", saveGeometry());
			settings.setValue("windowState", saveState());

			QMainWindow::closeEvent(event);
		}

		void MainWindowImpl::RestoreSettings() {
			QSettings settings("Shulzhenko corp", "Pawnengine");
			restoreGeometry(settings.value("geometry").toByteArray());
			restoreState(settings.value("windowState").toByteArray());
		}

		void MainWindowImpl::InitEngine() {
			m_Engine.reset(new pawn::engine::Engine);

			SetGameEngineWindowHWND(m_CentralWidget->GetWindowsHandle());

			pawn::system::InputManagerWindows::RegisterMouse();
			pawn::system::InputManagerWindows::RegisterKeyboard();

			m_Engine->Init(GetGameEngineWindowHWND(), EngineViewWidth, EngineViewHeight);

			std::shared_ptr<pawn::engine::GameScene>& scene{ m_Engine->GetScene() };

			m_Engine->UploadMeshFromFile("res\\assets\\models\\cube.obj");
			m_Engine->UploadMeshFromFile("res\\assets\\models\\sphere.obj");

			pawn::engine::GameEntity entity{ scene->CreateEntity("Cube") };
			entity.AddComponent<pawn::engine::MeshComponent>(m_Engine->GetMeshByPath("res\\assets\\models\\cube.obj"), "res\\assets\\models\\cube.obj");

			pawn::engine::GameEntity camera{ scene->CreateEntity("Camera") };
			pawn::engine::CameraComponent& cameraComponent{ camera.AddComponent<pawn::engine::CameraComponent>() };
			cameraComponent.Camera.SetPerspective();
			cameraComponent.IsActiveCamera = true;

			pawn::engine::TransformationComponent& transformationComponent = camera.GetComponent<pawn::engine::TransformationComponent>();
			transformationComponent.Position = glm::vec3(2.5f, 2.25f, 4.0f);
			transformationComponent.Rotation = glm::vec3(-0.5f, 0.5f, 0.3f);

			emit ActiveSceneChanged(scene);
		}

		void MainWindowImpl::InitConnections() {
			connect(
				this,
				SIGNAL(ActiveSceneChanged(std::shared_ptr<pawn::engine::GameScene>)),
				m_LeftPanel,
				SLOT(OnActiveSceneChanged(std::shared_ptr<pawn::engine::GameScene>))
			);

			connect(
				m_LeftPanel,
				SIGNAL(SelectedEntityChanged(pawn::engine::GameEntity)),
				m_RightPanel,
				SLOT(OnSelectedEntityChanged(pawn::engine::GameEntity))
			);

			connect(
				m_RightPanel,
				SIGNAL(EntityTagModified()),
				m_LeftPanel,
				SLOT(OnEntityTagModified())
			);
		}

	}

}
