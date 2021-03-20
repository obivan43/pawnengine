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
		m_TagItem = new QTreeWidgetItem(m_InspectorPanel);
		m_TagItem->setText(0, "Tag");
		m_TagItem->setHidden(true);

		m_TagWidgetWrapper = new QTreeWidgetItem(m_TagItem);
		m_TagWidgetWrapper->setHidden(true);

		m_TagItem->addChild(m_TagWidgetWrapper);

		m_TagLineEdit = new QLineEdit();
		m_TagLineEdit->setHidden(true);

		m_InspectorPanel->addTopLevelItem(m_TagItem);
		m_InspectorPanel->setItemWidget(m_TagWidgetWrapper, 0, m_TagLineEdit);
	}

	void RightPanelWidgetImpl::OnSelectedEntityChanged(pawn::Entity entity) {
		m_SelectedEntity = entity;
		RefreshPanel();
	}

	void RightPanelWidgetImpl::RefreshPanel() {
		if (!m_SelectedEntity.IsNull()) {
			pawn::TagComponent& tagComponent = m_SelectedEntity.GetComponent<pawn::TagComponent>();

			m_TagLineEdit->setText(tagComponent.Tag.c_str());

			m_TagItem->setHidden(false);
			m_TagWidgetWrapper->setHidden(false);
			m_TagLineEdit->setHidden(false);
		}
		else {
			m_TagItem->setHidden(true);
			m_TagWidgetWrapper->setHidden(true);
			m_TagLineEdit->setHidden(true);
		}
	}

	void RightPanelWidgetImpl::OnTagLineEditPress() {
		QString& text = m_TagLineEdit->text();

		if (!m_SelectedEntity.IsNull()) {
			std::string& tag = m_SelectedEntity.GetComponent<pawn::TagComponent>().Tag;
			tag = text.toLocal8Bit().constData();
		}

		emit EntityModified();
		m_TagLineEdit->clearFocus();
	}

	void RightPanelWidgetImpl::InitConnections() {
		connect(
			m_TagLineEdit, 
			SIGNAL(returnPressed()), 
			SLOT(OnTagLineEditPress())
		);
	}

}
