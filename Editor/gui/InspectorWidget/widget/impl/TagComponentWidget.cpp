#include "TagComponentWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

namespace editor {

	namespace impl {

		TagComponentWidget::TagComponentWidget(QWidget* parent)
			: QWidget(parent)
			, m_Tag(nullptr)
			, m_TagLineEdit(nullptr)
			, m_TagLabel(nullptr) {

			QVBoxLayout* layout = new QVBoxLayout(this);

			QHBoxLayout* tagLayout = new QHBoxLayout();

			m_TagLineEdit = new QLineEdit(this);

			m_TagLabel = new QLabel("Tag", this);
			m_TagLabel->setMinimumWidth(80);

			tagLayout->addWidget(m_TagLabel);
			tagLayout->addWidget(m_TagLineEdit);
			
			layout->addLayout(tagLayout);

			setLayout(layout);

			InitConnections();
		}

		void TagComponentWidget::SetTag(pawn::engine::TagComponent* tag) {
			m_Tag = tag;
			m_TagLineEdit->setText(m_Tag->Tag.c_str());
		}

		void TagComponentWidget::OnLineEditPress() {
			QString& text{ m_TagLineEdit->text() };

			m_Tag->Tag = text.toLocal8Bit().constData();

			emit TagModified();
			m_TagLineEdit->clearFocus();
		}

		void TagComponentWidget::InitConnections() {
			connect(
				m_TagLineEdit,
				SIGNAL(returnPressed()),
				this,
				SLOT(OnLineEditPress())
			);
		}

	}

}
