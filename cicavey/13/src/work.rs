#[derive(Debug)]
pub enum AoC {}

#[derive(Debug, Copy, Clone, Hash)]
struct Packet {
    value: i64,
}

pub fn run(input: &str, log: fn(String)) -> Result<(), AoC> {
    let lines: Vec<&str> = input.lines().collect();

    for c in lines.chunks(3) {
        log(format!("{}", c[0]));
    }

    Ok(())
}
