#include "pch.h"
#include "MainWindowImpl.h"

#include <string>

namespace impl {

	MainWindowImpl::MainWindowImpl(QWidget* parent)
		: MainWindow(parent)
		, m_BottomPanel(nullptr)
		, m_LeftPanel(nullptr) 
		, m_RightPanel(nullptr)
		, m_CentralWidget(nullptr) {
		setWindowTitle("Pawn Engine Editor");
		setWindowIcon(QIcon(":/pawn.png"));
		resize(EditorDefaultWidth, EditorDefaultHeight);

		m_CentralWidget = CentralWidget::CreateImpl(this);
		m_CentralWidget->setFixedSize(EngineViewWidth, EngineViewHeight);
		setCentralWidget(m_CentralWidget);

		m_BottomPanel = BottomPanelWidget::CreateImpl(this);
		m_RightPanel = RightPanelWidget::CreateImpl(this);
		m_LeftPanel = LeftPanelWidget::CreateImpl(this);

		addDockWidget(Qt::BottomDockWidgetArea, m_BottomPanel);
		addDockWidget(Qt::RightDockWidgetArea, m_RightPanel);
		addDockWidget(Qt::LeftDockWidgetArea, m_LeftPanel);

		InitConnections();
		InitEngine();
	}

	void MainWindowImpl::closeEvent(QCloseEvent* event) {
		Running = false;
	}

	void MainWindowImpl::InitEngine() {
		m_Engine.reset(new pawn::Engine);
		m_Engine->Init(m_CentralWidget->GetWindowsHandle(), EngineViewWidth, EngineViewHeight);

		std::shared_ptr<pawn::Scene>& scene = m_Engine->GetScene();

		m_Engine->UploadMeshFromFile("res\\assets\\models\\cube.obj");
		m_Engine->UploadMeshFromFile("res\\assets\\models\\sphere.obj");

		pawn::Entity entity = scene->CreateEntity("Sphere");
		entity.AddComponent<pawn::MeshComponent>(m_Engine->GetMeshByPath("res\\assets\\models\\sphere.obj"), "res\\assets\\models\\sphere.obj");

		pawn::Entity camera = scene->CreateEntity("Camera");
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
			SIGNAL(ActiveSceneChanged(std::shared_ptr<pawn::Scene>)),
			m_LeftPanel,
			SLOT(OnActiveSceneChanged(std::shared_ptr<pawn::Scene>))
		);

		connect(
			m_LeftPanel,
			SIGNAL(SelectedEntityChanged(pawn::Entity)),
			m_RightPanel,
			SLOT(OnSelectedEntityChanged(pawn::Entity))
		);

		connect(
			m_RightPanel,
			SIGNAL(EntityModified()),
			m_LeftPanel, SLOT(OnEntityModified())
		);
	}

}