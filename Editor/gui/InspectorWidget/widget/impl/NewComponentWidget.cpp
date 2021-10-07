#include "NewComponentWidget.h"

#include <QVBoxLayout>

namespace editor {

	namespace impl {

		NewComponentWidget::NewComponentWidget(QWidget* parent) 
			: QWidget(parent)
			, m_Entity(nullptr)
			, m_Button(nullptr) {

			QVBoxLayout* layout = new QVBoxLayout(this);

			m_Button = new QPushButton("New component", this);
			m_Button->setMinimumHeight(40);

			layout->addWidget(m_Button);

			setLayout(layout);

			InitConnections();
		}

		void NewComponentWidget::SetEntity(pawn::engine::GameEntity* entity) {
			m_Entity = entity;
		}

		void NewComponentWidget::OnPress() {

		}

		void NewComponentWidget::InitConnections() {
			connect(
				m_Button,
				SIGNAL(clicked()),
				this,
				SLOT(OnPress())
			);
		}

	}

}
