
#include "PawnEngine/engine/components/TagComponent.h"

#include <QtWidgets/QWidget>
#include <QLabel>
#include <QLineEdit>

namespace editor::impl {

	class TagComponentWidget : public QWidget {
		Q_OBJECT

		public:
			TagComponentWidget(QWidget* parent = Q_NULLPTR);

			void SetTag(pawn::engine::TagComponent* tag);

			QLineEdit* GetTagLineEdit() { return m_TagLineEdit; }

		signals:
			void TagModified();

		public slots:
			void OnLineEditPress();

		private:
			void InitConnections();

		private:
			pawn::engine::TagComponent* m_Tag;

			QLineEdit* m_TagLineEdit;
			QLabel* m_TagLabel;
	};
}
