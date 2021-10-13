#include "NewComponentWidget.h"

#include "SelectComponentWidget.h"

#include <QVBoxLayout>

namespace editor {

	namespace impl {

		NewComponentWidget::NewComponentWidget(QWidget* parent) 
			: QWidget(parent)
			, m_Entity(nullptr)
			, m_Button(nullptr)
			, m_SelectWidget(nullptr) {

			QVBoxLayout* layout = new QVBoxLayout(this);

			m_Button = new QPushButton("New component", this);
			m_Button->setMinimumHeight(40);

			m_SelectWidget = new SelectComponentWidget(this);

			layout->addWidget(m_Button);

			setLayout(layout);

			InitConnections();
		}

		void NewComponentWidget::SetEntity(pawn::engine::GameEntity* entity) {
			m_Entity = entity;
			m_SelectWidget->SetEntity(entity);
		}

		void NewComponentWidget::OnPress() {
			m_SelectWidget->Update();
			m_SelectWidget->exec();
		}

		void NewComponentWidget::InitConnections() {
			qRegisterMetaType<ComponentsEnum>("ComponentsEnum");
			connect(
				m_SelectWidget,
				SIGNAL(AddedNewComponent(ComponentsEnum)),
				this,
				SIGNAL(AddedNewComponent(ComponentsEnum)),
				Qt::QueuedConnection
			);

			connect(
				m_Button,
				SIGNAL(clicked()),
				this,
				SLOT(OnPress())
			);
		}

	}

}
