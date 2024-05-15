# Cub3d

&#91;2021.04 ~ 2021.07&#93;

- Cub3d is my favorite project in 42Seoul.<br />
  because, 프로그래밍적 사고가 익숙하지 않던시절, 비교적 적은 정보에서 끝까지 해결한 프로젝트입니다.<br />
  수학(삼각함수)를 활용한 첫프로젝트로 개발하는 동안 재미가 있었습니다.
- Posts about cub3d implementation: <a href="https://kirkim.github.io/tag/42seoul-ft-cub3d/" target="_blank">Cub3d - kirkim.github.io</a>

<br><br>

## Goal

Make virtual 3D environment using raycasting like <a href="https://fr.wikipedia.org/wiki/Wolfenstein_3D" target="_blank">Wolfenstein 3D</a>

<img src="https://kirkim.github.io/assets/storage/cub3d/Cub3d2.gif" alt="playing cub3d">

<br><br>

## Skills

- C language
- Makefile
- <a href="https://harm-smits.github.io/42docs/libs/minilibx" target="_blank">MinilibX</a>

<br><br>

## How to run

```
git clone git@github.com:kirkim/Cub3d.git
cd Cub3d
```

you can make two kinds of cub3d `basic` & `bonus`

### basic

```
make
./cub3d ./map/test.cub
```

### bonus

```
make bonus
./cub3d ./map/test_bonus.cub
```

<br><br>

## Controls

- `w, a, s, d`: move key.
- `←, ↑, →, ↓`: eyesight move key.
- `1`: open door key.
- `2`: close door key.
- `3`: turn on mouse mode.
- `4`: turn off mouse mode.
