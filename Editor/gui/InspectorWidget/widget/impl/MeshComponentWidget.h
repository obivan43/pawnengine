#pragma once

#include "PawnEngine/engine/GameEntity.h"
#include "PawnEngine/engine/components/MeshComponent.h"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

namespace editor::impl {

	class MeshComponentWidget : public QWidget {
		Q_OBJECT

		public:
			MeshComponentWidget(QWidget* parent = Q_NULLPTR);

			void SetEntity(pawn::engine::GameEntity* entity);
			void SetMesh(pawn::engine::MeshComponent* mesh);

			QLineEdit* GetMeshLineEdit() { return m_MeshLineEdit; }

		signals:
			void MeshModified(pawn::engine::GameEntity);

		public slots:
			void OnLineEditPress();

		private:
			void InitConnections();

		private:
			pawn::engine::GameEntity* m_Entity;
			pawn::engine::MeshComponent* m_Mesh;

			QLineEdit* m_MeshLineEdit;
			QLabel* m_MeshLabel;
	};

}
