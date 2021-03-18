#include "pch.h"
#include "MainWindow.h"
#include "TreeEntityWidgetItem.h"

#include <QtWidgets/QHBoxLayout>

#include "gtc/matrix_transform.hpp"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), m_EngineView(nullptr), m_SceneHierarchy(nullptr), m_SceneHierarchyDockWidget(nullptr), m_Engine(nullptr) {
	QHBoxLayout* layout = new QHBoxLayout(this);

	m_EngineView = new QFrame(this);
	m_EngineView->setMinimumSize(DefaultWidth, DefaultHeight);

	m_SceneHierarchy = new QTreeWidget(this);
	m_SceneHierarchy->setHeaderHidden(true);

	m_SceneHierarchyDockWidget = new QDockWidget("Scene Hierarchy", this);
	m_SceneHierarchyDockWidget->setWidget(m_SceneHierarchy);
	addDockWidget(Qt::LeftDockWidgetArea, m_SceneHierarchyDockWidget);

	m_Inspector = new QTreeWidget(this);
	m_Inspector->setHeaderHidden(true);

	m_InspectorDockWidget = new QDockWidget("Inspector", this);
	m_InspectorDockWidget->setWidget(m_Inspector);
	addDockWidget(Qt::LeftDockWidgetArea, m_InspectorDockWidget);

	setCentralWidget(m_EngineView);

	setWindowTitle("Pawn Engine Editor");
	setWindowIcon(QIcon(":/editor/pawn.png"));

	InitEngine();
	InitSceneHierarchy();
	InitInspectorPanel();

	connect(m_SceneHierarchy, SIGNAL(itemClicked(QTreeWidgetItem*, int)), SLOT(OnSceneHierarchyItemClecked(QTreeWidgetItem*, int)));
}

void MainWindow::closeEvent(QCloseEvent* event) {
	this->Running = false;
}

void MainWindow::InitEngine() {
	m_Engine.reset(new pawn::Engine);
	m_Engine->Init((HWND)m_EngineView->winId(), DefaultWidth, DefaultHeight);

	m_Engine->UploadMeshFromFile("res\\assets\\models\\cube.obj");
	m_Engine->UploadMeshFromFile("res\\assets\\models\\sphere.obj");

	pawn::Entity entity = m_Engine->GetScene()->CreateEntity("Sphere");
	entity.AddComponent<pawn::MeshComponent>(m_Engine->GetMeshByName("sphere"));

	pawn::Entity camera = m_Engine->GetScene()->CreateEntity("Camera");
	pawn::CameraComponent& cameraComponent = camera.AddComponent<pawn::CameraComponent>();
	cameraComponent.m_Camera.SetPerspective();
	cameraComponent.m_IsActiveCamera = true;

	pawn::TransformationComponent& transformationComponent = camera.GetComponent<pawn::TransformationComponent>();
	transformationComponent.m_Transformation = glm::translate(transformationComponent.m_Transformation, glm::vec3(0.0f, 0.0f, 4.0f));
}

void MainWindow::InitSceneHierarchy() {
	std::shared_ptr<pawn::Scene> scene = m_Engine->GetScene();
	entt::registry& registry = scene->GetRegistry();

	TreeEntityWidgetItem* root = new TreeEntityWidgetItem(pawn::Entity(), "Scene");
	m_SceneHierarchy->addTopLevelItem(root);

	registry.each([&](auto entityID) {
		pawn::Entity entity(entityID, scene.get());
		std::string& name = entity.GetComponent<pawn::NameComponent>().m_Name;
		
		TreeEntityWidgetItem* item = new TreeEntityWidgetItem(entity, name.c_str(), root);
		root->addChild((QTreeWidgetItem*)item);
	});
}

void MainWindow::InitInspectorPanel() {
	m_Tag = new QTreeWidgetItem(m_Inspector);
	m_Tag->setText(0, "Tag");
	m_Inspector->addTopLevelItem(m_Tag);
	m_Tag->setHidden(true);

	m_TagChild= new QTreeWidgetItem(m_Tag);
	m_TagChild->setHidden(true);

	entityLineEdit = new QLineEdit();
	entityLineEdit->setHidden(true);
	m_Inspector->setItemWidget(m_TagChild, 0, entityLineEdit);

	m_Tag->addChild(m_TagChild);

	m_Transformation = new QTreeWidgetItem(m_Inspector);
	m_Transformation->setText(0, "Transformation");
	m_Inspector->addTopLevelItem(m_Transformation);
	m_Transformation->setHidden(true);
}

void MainWindow::UpdateInspectorPanel() {
	if (!m_SelectedEntity.IsNull()) {
		pawn::NameComponent& nameComponent = m_SelectedEntity.GetComponent<pawn::NameComponent>();

		entityLineEdit->setText(nameComponent.m_Name.c_str());

		m_Tag->setHidden(false);
		m_TagChild->setHidden(false);
		entityLineEdit->setHidden(false);
	}
}

void MainWindow::OnSceneHierarchyItemClecked(QTreeWidgetItem* item, int index) {
	TreeEntityWidgetItem* entityWidgetItem = reinterpret_cast<TreeEntityWidgetItem*>(item);
	m_SelectedEntity = entityWidgetItem->GetEntity();
	UpdateInspectorPanel();
}