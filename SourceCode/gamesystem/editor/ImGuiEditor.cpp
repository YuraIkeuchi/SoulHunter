#include "ImGuiEditor.h"
#include "ModelManager.h"
#include "imgui.h"
ImGuiEditor::ImGuiEditor() {
	//ÉÇÉfÉãÇÃì«Ç›çûÇ›
	modelBox = ModelManager::GetInstance()->GetModel(ModelManager::BackBox);
	modelRock = ModelManager::GetInstance()->GetModel(ModelManager::BackRock);
	modelTorch = ModelManager::GetInstance()->GetModel(ModelManager::BackTorch);
	modelArg = ModelManager::GetInstance()->GetModel(ModelManager::Particle);
	IKEObject3d* backobj_[BackObj_Max];
	for (int i = 0; i < backobj.size(); i++) {
		backobj_[i] = new IKEObject3d();
		backobj_[i] = IKEObject3d::Create();
	}

	backobj_[Rock]->SetModel(modelRock);
	backobj_[Rock]->SetPosition(m_Pos);
	backobj_[Rock]->SetScale({ 0.25f, 0.25f, 0.25f });

	backobj_[Box]->SetModel(modelBox);
	backobj_[Box]->SetPosition(m_Pos);
	backobj_[Box]->SetScale({ 8.0f,8.0f,8.0f });

	backobj_[Torch]->SetModel(modelTorch);
	backobj_[Torch]->SetPosition(m_Pos);
	backobj_[Torch]->SetScale({ 3.0f,6.0f,1.0f });

	for (int i = 0; i < backobj.size(); i++) {
		backobj[i].reset(backobj_[i]);
	}

	IKEObject3d* argobj_ = new IKEObject3d();
	argobj_ = IKEObject3d::Create();
	argobj_->SetModel(modelArg);
	argobj_->SetScale({ 2.0f,2.0f,2.0f });
	argobj.reset(argobj_);

}

//çXêV
void ImGuiEditor::Update(const XMFLOAT3& pos) {
	m_Pos = { pos.x,pos.y,pos.z + m_Distance };
	for (int i = 0; i < backobj.size(); i++) {
		backobj[i]->SetPosition(m_Pos);
		backobj[i]->SetRotation(m_Rot);
		backobj[i]->Update();
	}

	argobj->SetPosition(m_Pos);
	argobj->SetColor({ 1.0f,1.0f,1.0f,0.5f });
	argobj->Update();
}

//ï`âÊ
const void ImGuiEditor::ObjDraw() {
	IKEObject3d::PreDraw();
	//ëIëÇµÇΩOBJÇ…ÇÊÇ¡Çƒï`âÊÇ∑ÇÈÇ‡ÇÃÇ™à·Ç§
	if (m_EditorType == ObjSet) {
		if (m_DrawObjType == DrawRock) {
			backobj[Rock]->Draw();
		}
		else if (m_DrawObjType == DrawBox) {
			backobj[Box]->Draw();
		}
		else if (m_DrawObjType == DrawTorch) {
			backobj[Torch]->Draw();
		}
	}
	else {
		argobj->Draw();
	}
}

//ìGÇÃê∂ê¨Imgui
const void ImGuiEditor::EditorImGuiDraw() {
	{
		//Ç«ÇÍÇê›íuÇ∑ÇÈÇ©
		ImGui::Begin("SelectEditorScene");
		ImGui::SetWindowPos(ImVec2(1000, 300));
		ImGui::SetWindowSize(ImVec2(280, 150));
		if (ImGui::Button("Enemy", ImVec2(90, 50))) {
			m_EditorType = EnemySet;
		}

		if (ImGui::Button("Obj", ImVec2(90, 50))) {
			m_EditorType = ObjSet;
		}

		if (ImGui::Button("EnemyObj", ImVec2(90, 50))) {
			m_EditorType = EnemyObjSet;
		}
		ImGui::End();
		//ìG
		if (m_EditorType == EnemySet) {
			ImGui::Begin("SetEnemy");
			ImGui::SetWindowPos(ImVec2(0, 500));
			ImGui::SetWindowSize(ImVec2(280, 230));
			if (ImGui::Button("NormalEnemy", ImVec2(90, 50))) {
				m_EnemyArgment = true;
				m_EnemyType = Normal;
			}

			if (ImGui::Button("ThornEnemy", ImVec2(90, 50))) {
				m_EnemyArgment = true;
				m_EnemyType = Thorn;
			}

			if (ImGui::Button("WingEnemy", ImVec2(90, 50))) {
				m_EnemyArgment = true;
				m_EnemyType = Wing;
			}

			if (ImGui::Button("BirdEnemy", ImVec2(90, 50))) {
				m_EnemyArgment = true;
				m_EnemyType = Bird;
			}
			ImGui::End();

			ImGui::Begin("m_DeleteEnemy");
			ImGui::SetWindowPos(ImVec2(280, 500));
			ImGui::SetWindowSize(ImVec2(280, 230));
			if (ImGui::Button("DeleteNormalEnemy", ImVec2(90, 50))) {
				m_DeleteEnemy = true;
				m_EnemyType = Normal;
			}

			if (ImGui::Button("DeleteThornEnemy", ImVec2(90, 50))) {
				m_DeleteEnemy = true;
				m_EnemyType = Thorn;
			}

			if (ImGui::Button("DeleteWingEnemy", ImVec2(90, 50))) {
				m_DeleteEnemy = true;
				m_EnemyType = Wing;
			}

			if (ImGui::Button("DeleteBirdEnemy", ImVec2(90, 50))) {
				m_DeleteEnemy = true;
				m_EnemyType = Bird;
			}
			ImGui::End();
		}
		//îwåiOBJ
		else if (m_EditorType == ObjSet) {
			ImGui::Begin("SetObj");
			ImGui::SetWindowPos(ImVec2(0, 500));
			ImGui::SetWindowSize(ImVec2(280, 230));
			if (ImGui::Button("BoxArg", ImVec2(90, 50))) {
				m_BackObjArgment = true;
				m_BackObjType = Box;
			}
			if (ImGui::Button("RockArg", ImVec2(90, 50))) {
				m_BackObjArgment = true;
				m_BackObjType = Rock;
			}
			if (ImGui::Button("TorchArg", ImVec2(90, 50))) {
				m_BackObjArgment = true;
				m_BackObjType = Torch;
			}
			ImGui::End();

			ImGui::Begin("DeleteObj");
			ImGui::SetWindowPos(ImVec2(280, 500));
			ImGui::SetWindowSize(ImVec2(280, 230));
			if (ImGui::Button("DeleteBox", ImVec2(90, 50))) {
				m_BackObjDelete = true;
				m_BackObjType = Box;
			}
			if (ImGui::Button("DeleteRock", ImVec2(90, 50))) {
				m_BackObjDelete = true;
				m_BackObjType = Rock;
			}
			if (ImGui::Button("DeleteTorch", ImVec2(90, 50))) {
				m_BackObjDelete = true;
				m_BackObjType = Torch;
			}
			ImGui::End();
		}
		//ìGÇÃOBJ
		else if (m_EditorType == EnemyObjSet) {
			ImGui::Begin("EnemySetObj");
			ImGui::SetWindowPos(ImVec2(0, 500));
			ImGui::SetWindowSize(ImVec2(280, 230));
			if (ImGui::Button("UpThornObj", ImVec2(90, 50))) {
				m_ThornObjArgment = true;
				m_ThornDir = Up;
			}
			if (ImGui::Button("DownThornObj", ImVec2(90, 50))) {
				m_ThornObjArgment = true;
				m_ThornDir = Down;
			}
			if (ImGui::Button("RightThornObj", ImVec2(90, 50))) {
				m_ThornObjArgment = true;
				m_ThornDir = Right;
			}
			if (ImGui::Button("LeftThornObj", ImVec2(90, 50))) {
				m_ThornObjArgment = true;
				m_ThornDir = Left;
			}
			ImGui::End();

			ImGui::Begin("DeleteThornObj");
			ImGui::SetWindowPos(ImVec2(280, 500));
			ImGui::SetWindowSize(ImVec2(280, 230));
			if (ImGui::Button("DeleteThornObj", ImVec2(90, 50))) {
				m_DeleteThornObj = true;
			}
			ImGui::End();
		}
	}

	{
		//É}ÉbÉvêÿÇËë÷Ç¶
		ImGui::Begin("DrawObj");
		ImGui::SetWindowPos(ImVec2(840, 500));
		ImGui::SetWindowSize(ImVec2(100, 230));
		if (ImGui::Button("DrawBox", ImVec2(90, 50))) {
			m_DrawObjType = DrawBox;
		}
		if (ImGui::Button("DrawRock", ImVec2(90, 50))) {
			m_DrawObjType = DrawRock;
		}
		if (ImGui::Button("DrawTorch", ImVec2(90, 50))) {
			m_DrawObjType = DrawTorch;
		}

		ImGui::SliderFloat("rot.x", &m_Rot.x, 0.0f, 360.0f);
		ImGui::SliderFloat("rot.y", &m_Rot.y, 0.0f, 360.0f);
		ImGui::SliderFloat("rot.z", &m_Rot.z, 0.0f, 360.0f);
		ImGui::SliderFloat("distance", &m_Distance, -5.0f, 10.0f);
		ImGui::End();
	}
}