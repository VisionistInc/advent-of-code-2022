use std::cmp::max;

type AocErr = ();

pub fn run(input: &str, log: fn(String)) -> Result<(), AocErr> {
    // log(format!("{:?}", s));

    let mut data: Vec<Vec<u32>> = vec![];
    let mut vis: Vec<Vec<u32>> = vec![];

    for line in input.lines() {
        let values: Vec<u32> = line.chars().map(|c| c.to_digit(10).unwrap()).collect();
        let v: Vec<u32> = vec![0; values.len()];
        data.push(values);
        vis.push(v);
    }

    let size = data.len();

    let mut internal_vis_count = 0;

    internal_vis_count = 2 * size + 2 * (size - 2);

    for y in 1..size - 1 {
        for x in 1..size - 1 {
            let curr = data[y][x];
            // log(format!("{:?}", data[y][x]));

            // Need to check line of sight in each direction
            let mut vis_north = 1;
            let mut scn_north = 0;
            for vy in (0..=y - 1).rev() {
                scn_north += 1;
                if data[vy][x] >= curr {
                    vis_north = 0;
                    break;
                }
            }

            let mut vis_south = 2;
            let mut scn_south = 0;
            for vy in y + 1..size {
                scn_south += 1;
                if data[vy][x] >= curr {
                    vis_south = 0;
                    break;
                }
            }

            let mut vis_east = 4;
            let mut scn_east = 0;
            for vx in x + 1..size {
                scn_east += 1;
                if data[y][vx] >= curr {
                    vis_east = 0;
                    break;
                }
            }

            let mut vis_west = 8;
            let mut scn_west = 0;
            for vx in (0..=x - 1).rev() {
                scn_west += 1;
                if data[y][vx] >= curr {
                    vis_west = 0;
                    break;
                }
            }

            // vis[y][x] = vis_north | vis_south | vis_east | vis_west;
            vis[y][x] = scn_north * scn_south * scn_west * scn_east;

            if vis[y][x] > 0 {
                internal_vis_count += 1;
            }
        }
    }

    log(format!("{:?}", internal_vis_count));

    let mut scn_max = 0;

    for y in 1..size - 1 {
        for x in 1..size - 1 {
            scn_max = max(vis[y][x], scn_max);
        }
    }

    log(format!("{:?}", scn_max));

    Ok(())
}
