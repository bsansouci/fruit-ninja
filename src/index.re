open Reprocessing;

type state = {
  orange: imageT,
  orangeHalf1: imageT,
  orangeHalf2: imageT
};

let setup = (env) => {
  Env.size(~width=600, ~height=600, env);
  {
    orange: Draw.loadImage(~filename="orange.png", env),
    orangeHalf1: Draw.loadImage(~filename="orange_half_1_copy.png", env),
    orangeHalf2: Draw.loadImage(~filename="orange_half_2_copy.png", env),
  }
};

let draw = (state, env) => {
  Draw.background(Utils.color(~r=100, ~g=80, ~b=29, ~a=255), env);
  Draw.image(state.orange, ~pos=(0, 0), ~width=64, ~height=64, env);
  Draw.image(state.orangeHalf1, ~pos=(80, 10), ~width=64, ~height=64, env);
  Draw.image(state.orangeHalf2, ~pos=(100, 10), ~width=64, ~height=64, env);
  state
};

run(~setup, ~draw, ());
