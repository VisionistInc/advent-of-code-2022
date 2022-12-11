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

fn follow(head: Point2D<i32, AoC>, tail: Point2D<i32, AoC>) -> Point2D<i32, AoC> {
    let dist = head - tail;
    let dist_abs = dist.abs();

    let mut new_tail = tail.clone();

    // Tail is adjacent or on top of, no problem
    if dist_abs.x <= 1 && dist_abs.y <= 1 {
        return new_tail;
    } else {
        if tail.x == head.x {
            // tail must move in the y direction toward head
            new_tail.y += dist.y.signum();
        } else if tail.y == head.y {
            // tail must move in the x direction toward head
            new_tail.x += dist.x.signum();
        } else {
            // diagonal move
            new_tail.y += dist.y.signum();
            new_tail.x += dist.x.signum();
        }
    }

    new_tail
}

fn simulate(input: &str, knots: usize) -> usize {
    let mut rope: Vec<Point2D<i32, AoC>> = vec![point2(0, 0); knots];
    let mut grid: Grid = Grid::new();
    grid.data.insert(*rope.last().unwrap(), GridState::Occupied);

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
            // move the head
            rope[0] += step_vec;

            // update each knot in sequence with the one before it
            for i in 0..rope.len() - 1 {
                rope[i + 1] = follow(rope[i], rope[i + 1]);
            }

            // Only track tail pos
            grid.data.insert(*rope.last().unwrap(), GridState::Occupied);
        }
    }

    grid.occupied()
}

pub fn run(input: &str, log: fn(String)) -> Result<(), AoC> {
    log(format!("knots=2, visited={:?}", simulate(input, 2)));
    log(format!("knots=10, visited={:?}", simulate(input, 10)));
    Ok(())
}
