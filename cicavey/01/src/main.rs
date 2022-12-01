use std::{
    cmp::max,
    fs::File,
    io::{BufRead, BufReader},
};

fn main() {
    let file = File::open("input.txt").unwrap();
    let reader = BufReader::new(file);

    let mut elves = Vec::new();
    let mut cur_elf = Vec::new();
    let mut max_cal = 0;
    for line in reader.lines() {
        let s = line.unwrap();
        if s.is_empty() {
            let total = cur_elf.iter().sum();
            max_cal = max(max_cal, total);
            elves.push(total);
            cur_elf = Vec::new()
        } else {
            let v: i64 = s.parse().unwrap();
            cur_elf.push(v);
        }
    }
    // note - last input is empty, handles edge case
    println!("{:?}", max_cal);

    elves.sort();
    elves.reverse();

    let top_3: i64 = (&elves[0..=2]).iter().sum();

    println!("{:?}", top_3);
}
