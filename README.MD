# Conway's Game of Life in C++

A simple and smooth cellular automata simulator built using **C++** and the Raylib library. It lets you run Conway's original game alongside a few other fun rules, tweak color themes, and watch patterns evolve on a toroidal grid.

## Features

- **Multiple Rulesets:** Switch between Conway's Life, HighLife, Seeds, and more right while it's running.
- **Wrap-around Grid:** The edges wrap around, so nothing gets lost off-screen.
- **Color Themes:** Press `B` to jump into theme mode and change up the look.
- **Live Counter:** Keeps track of how many cells are alive in real-time.

## Controls

| Key | What it does |
| :--- | :--- |
| `R` | Randomize / Reset the grid |
| `B` | Toggle theme / background customization mode |
| `1` – `5` | Switch rules (when not in theme mode) |
| `1` – `4` | Switch color palettes (when in theme mode) |

## Included Rules

1. **Conway's Life (Default):** The classic B3/S23 rules.
2. **HighLife:** Similar to Conway's, but with a twist (B36/S23).
3. **Seeds:** Chaotic rule where everything dies unless it gets exactly 2 neighbors (B2/S).
4. **Life Without Death:** Cells never die once they're born (B3/S012345678).
5. **Custom Rule:** A dense, growth-heavy rule set with swarm like behaviour.

## Running It

Make sure you have **Raylib** installed. If you're on Linux/macOS, you can compile it via terminal like this:

```bash
g++ main.cpp -o game_of_life -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
