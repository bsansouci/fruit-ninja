open Reprocessing;
let g = 200.;
let fruitSize = 64;
let fruitSizef = 64.;

type objectT = {
  x: float,
  y: float,
  vx: float,
  vy: float,
  r: float,
  vr: float,
  img: imageT,
};

type state = {
  fruits: list(objectT),
  halves: list(objectT),
  bg: imageT,
  orange: imageT,
  orangeHalf1: imageT,
  orangeHalf2: imageT,
};

let spawnFruit = state => {
  ...state,
  fruits: [
    {
      x: Utils.randomf(~min=100., ~max=500.),
      y: 600.,
      r: 0.,
      vr: Utils.randomf(~min=-5., ~max=5.),
      vx: Utils.randomf(~min=-100., ~max=100.),
      vy: (-400.) +. Utils.randomf(~min=-100., ~max=100.),
      img: state.orange,
    },
    ...state.fruits,
  ],
};

let drawWithRotation = (img, ~pos as (x, y), ~height, ~width, ~rot, env) => {
  Draw.pushMatrix(env);
  Draw.translate(~x, ~y, env);
  Draw.rotate(rot, env);
  Draw.translate(
    ~x=float_of_int(width) /. (-2.),
    ~y=float_of_int(height) /. (-2.),
    env,
  );
  Draw.image(img, ~pos=(0, 0), ~height, ~width, env);
  Draw.popMatrix(env);
};

let applyGravity = (dt, g, {x, y, r, vr, vx, vy, img}) => {
  x: x +. dt *. vx,
  y: y +. dt *. vy,
  r: r +. dt *. vr,
  vr,
  vy: vy +. dt *. g,
  vx,
  img,
};

let drawObjectList = (l, env) =>
  List.iter(
    ({x, y, r, img}) =>
      drawWithRotation(
        img,
        ~pos=(x, y),
        ~width=fruitSize,
        ~height=fruitSize + 20,
        ~rot=r,
        env,
      ),
    l,
  );

let setup = env => {
  Env.size(~width=600, ~height=600, env);
  spawnFruit({
    fruits: [],
    halves: [],
    bg: Draw.loadImage(~filename="./assets/background.png", env),
    orange: Draw.loadImage(~filename="./assets/pineapple_small.png", env),
    orangeHalf1:
      Draw.loadImage(~filename="./assets/pineapple_half_1_small.png", env),
    orangeHalf2:
      Draw.loadImage(~filename="./assets/pineapple_half_2_small.png", env),
  });
};

let draw = (state, env) => {
  let dt = Env.deltaTime(env);
  let bottom = float_of_int(Env.height(env));
  Draw.background(Utils.color(~r=100, ~g=80, ~b=29, ~a=255), env);
  Draw.image(state.bg, ~pos=(0, 0), env);
  drawObjectList(state.halves, env);
  drawObjectList(state.fruits, env);

  let state = Utils.random(~min=0, ~max=50) == 1 ? spawnFruit(state) : state;

  let state = {
    ...state,
    fruits: List.map(applyGravity(dt, g), state.fruits),
    halves: List.map(applyGravity(dt, g *. 4.), state.halves),
  };
  let (mx, my) = Env.mouse(env);
  let mousef = (float_of_int(mx), float_of_int(my));
  let halfFruitf = fruitSizef /. 2.;
  let halfFruitf = 0.;
  let (sliced, unsliced) =
    List.partition(
      ({x, y}) =>
        Utils.distf(~p1=(x +. halfFruitf, y +. halfFruitf), ~p2=mousef)
        < fruitSizef
        -. 20.,
      state.fruits,
    );
  let calcVY = r => {
    let vy = -. Utils.randomf(~min=100., ~max=300.);
    sin(r) > 0. ? -. vy : vy /. 100.;
  };
  let newHalves =
    List.flatten(
      List.map(
        ({x, y, r}) => [
          {
            x,
            y: y +. 5.,
            vx: Utils.randomf(~min=-30., ~max=30.),
            vy: calcVY(r),
            r,
            vr: 0.,
            img: state.orangeHalf1,
          },
          {
            x,
            y: y -. 5.,
            vx: Utils.randomf(~min=-30., ~max=50.),
            vy: -. calcVY(r),
            r,
            vr: 0.,
            img: state.orangeHalf2,
          },
        ],
        sliced,
      ),
    );

  let state = {...state, fruits: unsliced, halves: state.halves @ newHalves};

  /* Remove old stuff */
  let state = {
    ...state,
    fruits: List.filter(({y}) => y < bottom, state.fruits),
    halves: List.filter(({y}) => y < bottom, state.halves),
  };

  state;
};

run(~setup, ~draw, ());
