## 🛠️ DirectX11 3D 렌더링 엔진 데모 <br></br> 
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
<br></br>
<br></br>

## 🎨 모델 렌더링
----------------
### 애니메이션
<br></br>
<img src="https://github.com/mng990/DirectX113D/assets/62287856/e6fc46dc-40b2-4ee0-b053-afbd93a6cdb4" align="left"></img>
<br></br>
<br></br>

스키닝과 트위닝으로 자연스러운 모션과 <br>
부드러운 애니메이션 간 전환을 구현했습니다.

<br></br>
<br></br>

### 인스턴싱
<br></br>
<img src="https://github.com/mng990/DirectX113D/assets/62287856/30b13a91-a96d-4947-9b47-ba92095f3a34" align="left"></img>
<br></br>
<br></br>

동일한 메쉬와 머테리얼을 가진 여러 물체의 위치 정보를 모아<br>
하나의 자료형으로 전달해 드로우콜을 줄였습니다.

<br></br>
<br></br>

## 🗻 지형/파티클
---------
### Greed (Height Map)
<br></br>
<img src="https://github.com/mng990/DirectX113D/assets/62287856/2fc87110-dd92-49eb-9457-d79b6c6a66ce" align="left"></img>
<br></br>
<br></br>

8비트 포멧의 Height Map 정보를 파싱해 <br>
그리드의 높낮이를 렌더링 했습니다.<br>

<br></br>
<br></br>

### Sky Box
<br></br>
<img src="https://github.com/mng990/DirectX113D/assets/62287856/123047d4-0907-45db-8f26-580ebb1bca59" align="left"></img>
<br></br>
<br></br>

카메라를 구의 중심에 고정한 후 <br>
회전 방향에  Sky box를 구현했습니다.<br>

<br></br>
<br></br>

### Billboard
<br></br>
<img src="https://github.com/mng990/DirectX113D/assets/62287856/19e014f5-9c19-4e3c-9112-f478dc667620" align="left"></img>
<br></br>
<br></br>

카메라의 시선 벡터와 물체의 위치 정보를 통해<br>
물체가 카메라의 시선 벡터에 맞춰 회전하도록 구현했습니다. <br>


<br></br>
<br></br>


## 🎯 Collision
------------
### ray picking
<br></br>
<img src="https://github.com/mng990/DirectX113D/assets/62287856/b53b4176-c678-4151-9bd3-988bb9ba6125" align="left"></img>
<br></br>
<br></br>

뷰포트(2D)에서 월드 스페이스(3D)로 좌표를 변환시켜 <br>
마우스가 위치한 지점에서 빛을 쏴 <br>
충돌한 물체가 클릭에 반응하도록 했습니다.<br>

<br></br>
<br></br>

### Button Demo (응용)
<br></br>
<img src="https://github.com/mng990/DirectX113D/assets/62287856/e4cf682d-411e-4cff-8042-4a60d8edd085" align="left"></img>
<br></br>
<br></br>

Orthographic 카메라로 <br>
특정 위치에 고정된 버튼을 그린 후 <br>
Ray Picking으로 사용자 입력에 반응하도록 구현했습니다. <br> 

<br></br>
<br></br>

## 💡 조명
-----------------
### Ambient / Diffuse / Specular
<br></br>
<img src="https://github.com/mng990/DirectX113D/assets/62287856/e0d9e927-7a7b-452d-b360-c4dc04754ced" align="left"></img>
<br></br>
<br></br>

물체와 빛의 Ambient, Diffuse, Specular 정보를 섞어 <br>
빛의 방향에 따른 자연스러운 색상을 구현했습니다.

<br></br>

### Emissive
<br></br>
<img src="https://github.com/mng990/DirectX113D/assets/62287856/6ec8e0e6-0625-469b-986c-79a0fe461ed4" align="left"></img>
<br></br>
<br></br>

카메라의 시선 벡터와 물체의 노말 벡터를 섞어 <br>
회전과 무관하게 물체의 외곽선을 강조하는 조명을 구현했습니다.

<br></br>
<br></br>

### Normal Mapping
<br></br>
<img src="https://github.com/mng990/DirectX113D/assets/62287856/0245fead-a49c-4499-b65c-7aab5dc34bf1" align="left"></img>
<br></br>
<br></br>

RGB 정보로 저장된 노말맵을 파싱한 후 <br>
해당 정보를 Tangent Space에서 World Space로 변환해 <br>
물체의 디테일한 질감을 구현했습니다.

<br></br>
<br></br>


