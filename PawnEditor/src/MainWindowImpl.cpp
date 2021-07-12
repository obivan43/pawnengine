#include "pch.h"
#include "MainWindowImpl.h"

#include <QSettings>
#include <string>

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
		connect(m_RightPanel, SIGNAL(EntityMeshModfied(pawn::GameEntity)), m_EngineManager, SLOT(OnEntityMeshModified(pawn::GameEntity)));
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
		m_Engine.reset(new pawn::Engine);
		m_Engine->Init(m_CentralWidget->GetWindowsHandle(), EngineViewWidth, EngineViewHeight);

		std::shared_ptr<pawn::GameScene>& scene = m_Engine->GetScene();

		m_Engine->UploadMeshFromFile("res\\assets\\models\\cube.obj");
		m_Engine->UploadMeshFromFile("res\\assets\\models\\sphere.obj");

		pawn::GameEntity entity = scene->CreateEntity("Sphere");
		entity.AddComponent<pawn::MeshComponent>(m_Engine->GetMeshByPath("res\\assets\\models\\sphere.obj"), "res\\assets\\models\\sphere.obj");

		pawn::GameEntity camera = scene->CreateEntity("Camera");
		pawn::CameraComponent& cameraComponent = camera.AddComponent<pawn::CameraComponent>();
		cameraComponent.Camera.SetPerspective();
		cameraComponent.IsActiveCamera = true;

		pawn::TransformationComponent& transformationComponent = camera.GetComponent<pawn::TransformationComponent>();
		transformationComponent.Position = glm::vec3(0.0f, 0.0f, 4.0f);

		emit ActiveSceneChanged(scene);
	}

	void MainWindowImpl::InitConnections() {
		connect(
			this,
			SIGNAL(ActiveSceneChanged(std::shared_ptr<pawn::GameScene>)),
			m_LeftPanel,
			SLOT(OnActiveSceneChanged(std::shared_ptr<pawn::GameScene>))
		);

		connect(
			m_LeftPanel,
			SIGNAL(SelectedEntityChanged(pawn::GameEntity)),
			m_RightPanel,
			SLOT(OnSelectedEntityChanged(pawn::GameEntity))
		);

		connect(
			m_RightPanel,
			SIGNAL(EntityTagModified()),
			m_LeftPanel, 
			SLOT(OnEntityTagModified())
		);
	}

}