use std::{collections::HashMap, fmt};

use euclid::{point2, vec2, Point2D, Vector2D};

#[derive(Debug)]
pub enum AoC {}

#[derive(Debug, Clone, Copy, PartialEq)]
enum GridState {
    Occupied,
    Unoccupied,
}

impl fmt::Display for GridState {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match *self {
            GridState::Occupied => write!(f, "#"),
            GridState::Unoccupied => write!(f, "."),
        }
    }
}

impl Default for GridState {
    fn default() -> Self {
        GridState::Unoccupied
    }
}

#[derive(Debug, Clone, PartialEq)]
struct Grid {
    w: i32,
    h: i32,
    data: HashMap<Point2D<i32, AoC>, GridState>,
}

impl Grid {
    pub fn new() -> Grid {
        Grid {
            w: 0,
            h: 0,
            data: HashMap::new(),
        }
    }

    // pub fn display(&self) {
    //     for y in 0..self.h {
    //         for x in 0..self.w {
    //             match self.data.get(&point2(x, y)) {
    //                 Some(s) => print!("{}", s),
    //                 _ => {}
    //             }
    //         }
    //         println!();
    //     }
    // }

    pub fn occupied(&self) -> usize {
        self.data
            .values()
            .filter(|&v| v == &GridState::Occupied)
            .count()
    }
}

pub fn run(input: &str, log: fn(String)) -> Result<(), AoC> {
    // log(format!("{:?}", s));

    let mut grid: Grid = Grid::new();
    let mut head: Point2D<i32, AoC> = point2(0, 0);
    let mut tail: Point2D<i32, AoC> = point2(0, 0);

    // let mut rope: Vec<Point2D<i32, AoC>> = vec![point2(0, 0); 10];

    grid.data.insert(tail, GridState::Occupied);

    for line in input.lines() {
        let ins: Vec<&str> = line.split_whitespace().collect();
        let dir = ins[0];
        let q: i32 = ins[1].parse().unwrap();

        // Convert into a unit vector
        let step_vec: Vector2D<i32, AoC> = match dir {
            "L" => vec2(-1, 0),
            "R" => vec2(1, 0),
            "U" => vec2(0, 1),
            "D" => vec2(0, -1),
            _ => vec2(0, 0),
        };

        for _ in 0..q {
            head += step_vec;

            // tail update logic, executed per step
            let dist = (head - tail);
            let dist_abs = dist.abs();

            // Tail is adjacent or on top of, no problem
            if dist_abs.x <= 1 && dist_abs.y <= 1 {
                continue;
            } else {
                if tail.x == head.x {
                    // tail must move in the y direction toward head
                    tail.y += dist.y.signum();
                } else if tail.y == head.y {
                    // tail must move in the x direction toward head
                    tail.x += dist.x.signum();
                } else {
                    // diagonal move
                    tail.y += dist.y.signum();
                    tail.x += dist.x.signum();
                }

                grid.data.insert(tail, GridState::Occupied);
            }
        }
        // log(format!("head={:?}, tail={:?}", head, tail));
    }

    log(format!("visited={:?}", grid.occupied()));

    Ok(())
}
