## 적을 추가할 경우

- [ ] 오브젝트를 그리는 함수를 동일하게 가져온다? or 적을 그냥 오브젝트 형태로 동일하게 넣어두기
- [ ] 기본 포지션에서 적에서부터 플레이어까지 레이 한개를 쐈을때 만나면 그 좌표까지 a*알고리즘을 돌린다
- [ ] 특정 범위까지 접근하면 3초에 한번씩 총을 쏜다 (distance 계산)
- [ ] 플레이어가 총을 쐈을때 player_rad방향으로 레이 하나를 쏴서 적에게 맞으면 가지고있는 hp를 깎는다(이게 말이 되는지 문제 배열안에 있는 적을 찾아가야함)
- [ ] 플레이어가 총을 쐈을때 WINDOW_W / 2 - enamie_width < enamie_x < WINDOW_W / 2 + enamie_width && player_shot == TRUE인 적이있으면 그 state는 pain
- [ ] state는 alive, pain, shoot, death로 구성
