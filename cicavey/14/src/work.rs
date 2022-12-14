use std::{collections::HashMap, fmt, vec};

use euclid::{point2, vec2, Point2D, Vector2D};

#[derive(Debug)]
pub enum AoC {}

#[derive(Debug, Clone, Copy, PartialEq)]
enum GridState {
    Empty,
    Rock,
    Sand,
}

impl fmt::Display for GridState {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match *self {
            GridState::Rock => write!(f, "#"),
            GridState::Empty => write!(f, "."),
            GridState::Sand => write!(f, "o"),
        }
    }
}

impl Default for GridState {
    fn default() -> Self {
        GridState::Empty
    }
}

#[derive(Debug, Clone, PartialEq)]
struct Grid {
    w: i32,
    h: i32,
    data: HashMap<Point2D<i64, AoC>, GridState>,
}

impl Grid {
    pub fn new() -> Grid {
        Grid {
            w: 0,
            h: 0,
            data: HashMap::new(),
        }
    }

    pub fn is(&self, p: Point2D<i64, AoC>, g: GridState) -> bool {
        *self.data.get(&p).unwrap_or(&GridState::Empty) == g
    }
}

fn part1(grid: &mut Grid, log: fn(String)) {
    let max_y = grid.data.iter().map(|p| p.0.y).max().unwrap();
    let mut inf_falling = false;
    let mut sand_count: u64 = 0;
    while !inf_falling {
        // for _hourglass in 0..25 {
        let mut sand: Point2D<i64, AoC> = point2(500, 0);

        loop {
            if sand.y > max_y {
                // infinite falling
                inf_falling = true;
                break;
            }

            let mut next = sand + vec2(0, 1);

            if grid.is(next, GridState::Empty) {
                sand = next;
                continue;
            }

            next = sand + vec2(-1, 1);
            if grid.is(next, GridState::Empty) {
                sand = next;
                continue;
            }

            next = sand + vec2(1, 1);
            if grid.is(next, GridState::Empty) {
                sand = next;
                continue;
            }

            // sand comes to rest

            break;
        }

        if !inf_falling {
            grid.data.insert(sand, GridState::Sand);
            sand_count += 1;
        }
    }

    log(format!("{:?}", sand_count));
}

fn part2(grid: &mut Grid, log: fn(String)) {
    let max_y = grid.data.iter().map(|p| p.0.y).max().unwrap();

    let min_x = grid.data.iter().map(|p| p.0.x).min().unwrap();
    let max_x = grid.data.iter().map(|p| p.0.x).max().unwrap();

    // force a really long line into the grid, could probably just check for y and rest...
    for x in min_x - 1000..max_x + 1000 {
        grid.data.insert(point2(x, max_y + 2), GridState::Rock);
    }

    let mut sand_count: u64 = 0;
    'outer: loop {
        // for _hourglass in 0..25 {
        let mut sand: Point2D<i64, AoC> = point2(500, 0);

        loop {
            let mut next = sand + vec2(0, 1);

            if grid.is(next, GridState::Empty) {
                sand = next;
                continue;
            }

            next = sand + vec2(-1, 1);
            if grid.is(next, GridState::Empty) {
                sand = next;
                continue;
            }

            next = sand + vec2(1, 1);
            if grid.is(next, GridState::Empty) {
                sand = next;
                continue;
            }

            // sand didn't move
            if sand == point2(500, 0) {
                sand_count += 1;
                break 'outer;
            }

            // sand comes to rest

            break;
        }

        grid.data.insert(sand, GridState::Sand);
        sand_count += 1;
    }

    log(format!("{:?}", sand_count));
}

pub fn run(input: &str, log: fn(String)) -> Result<(), AoC> {
    let mut grid = Grid::new();

    for line in input.lines() {
        let s: Vec<&str> = line.split(" -> ").collect();
        for pair in s.windows(2) {
            let a: Vec<i64> = pair[0].split(",").map(|v| v.parse().unwrap()).collect();
            let b: Vec<i64> = pair[1].split(",").map(|v| v.parse().unwrap()).collect();

            let pa: Point2D<i64, AoC> = point2(a[0], a[1]);
            let pb: Point2D<i64, AoC> = point2(b[0], b[1]);
            let mut delta = pa - pb;
            if delta.x != 0 {
                delta.x = -delta.x.signum();
            }
            if delta.y != 0 {
                delta.y = -delta.y.signum();
            }
            let mut pi = pa;
            while pi != pb {
                grid.data.insert(pi, GridState::Rock);
                pi += delta;
            }
            grid.data.insert(pi, GridState::Rock);
        }
    }

    part1(&mut grid.clone(), log);
    part2(&mut grid.clone(), log);

    Ok(())
}
