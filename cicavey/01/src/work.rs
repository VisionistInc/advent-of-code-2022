use std::cmp::max;

pub fn run(input: &str, log: fn(String)) {
    let mut elves = Vec::new();
    let mut cur_elf = Vec::new();
    let mut max_cal = 0;
    for line in input.lines() {
        if line.is_empty() {
            let total: i64 = cur_elf.iter().sum();
            max_cal = max(max_cal, total);
            elves.push(total);
            cur_elf = Vec::new()
        } else {
            let v: i64 = line.parse().unwrap();
            cur_elf.push(v);
        }
    }
    // note - last input is empty, handles edge case

    log(max_cal.to_string());

    elves.sort();
    elves.reverse();

    let top_3: i64 = (&elves[0..=2]).iter().sum();

    log(top_3.to_string());
}
