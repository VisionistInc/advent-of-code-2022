use std::cmp::{max, min};


type AocErr = ();

pub fn run(input: &str, log: fn(String)) -> Result<(), AocErr> {

    let mut contained = 0;
    let mut overlap = 0;

    for line in input.lines() {

        let v: Vec<&str> = line.split(&['-', ','][..]).collect();
        let n: Vec<i64> = v.iter().map(|x| x.parse().unwrap()).collect();

        
        if n[0] >= n[2] && n[1] <= n[3] { // first contained in second
            contained += 1;
        } else if n[2] >= n[0] && n[3] <= n[1] { // second contained in first
            contained += 1;
        }

        if n[0] >= n[2] && n[0] <= n[3] {
            overlap += 1;
        } else if n[1] >= n[2] && n[1] <= n[3] {
            overlap += 1;
        } else if n[2] >= n[0] && n[2] <= n[1] { 
            overlap += 1;
        } else if n[3] >= n[0] && n[3] <= n[1] { 
            overlap += 1;
        }

    }

    log(format!("{:?} {:?}", contained, overlap));

    Ok(())
}
