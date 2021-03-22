#include "pch.h"
#include "RightPanelWidgetImpl.h"

namespace impl {

	RightPanelWidgetImpl::RightPanelWidgetImpl(QWidget* parent) : RightPanelWidget(parent) {
		m_InspectorPanel = new QTreeWidget(this);
		m_InspectorPanel->setHeaderHidden(true);

		setWindowTitle("Inspector");
		setWidget(m_InspectorPanel);

		InitTagComponent();
		InitConnections();
	}

	void RightPanelWidgetImpl::InitTagComponent() {
		m_TagComponentInspectorWidget = new TagComponentWidgetItem(m_InspectorPanel);
		m_TagComponentInspectorWidget->setHidden(true);

		m_InspectorPanel->addTopLevelItem(m_TagComponentInspectorWidget);
		m_InspectorPanel->setItemWidget(m_TagComponentInspectorWidget->GetWrapper(), 0, m_TagComponentInspectorWidget->GetTagComponentWidget());
	}

	void RightPanelWidgetImpl::OnSelectedEntityChanged(pawn::Entity entity) {
		m_SelectedEntity = entity;
		m_TagComponentInspectorWidget->SetEntity(&m_SelectedEntity);
		RefreshPanel();
	}

	void RightPanelWidgetImpl::RefreshPanel() {
		if (!m_SelectedEntity.IsNull()) {
			pawn::TagComponent& tagComponent = m_SelectedEntity.GetComponent<pawn::TagComponent>();

			QLineEdit* lineEdit = m_TagComponentInspectorWidget->GetTagComponentWidget();
			lineEdit->setText(tagComponent.Tag.c_str());

			m_TagComponentInspectorWidget->setHidden(false);
		}
		else {
			m_TagComponentInspectorWidget->setHidden(true);
		}
	}

	void RightPanelWidgetImpl::InitConnections() {
		connect(
			m_TagComponentInspectorWidget,
			SIGNAL(EntityTagModified()),
			this,
			SIGNAL(EntityModified()),
			Qt::QueuedConnection
		);
	}

}
