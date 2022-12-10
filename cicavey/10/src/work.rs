#[derive(Debug)]
pub enum AoC {}

pub fn check(x: i64, cycles: i64) -> i64 {
    if cycles > 19 && (cycles - 20) % 40 == 0 {
        return x * cycles;
    }

    0
}

pub fn draw(x: i64, cycles: i64) -> bool {
    // Sprint is at x-1, x, x+1
    let c = (cycles - 1) % 40;
    c == ((x - 1) % 40) || c == (x % 40) || c == ((x + 1) % 40)
}

pub fn run(input: &str, log: fn(String)) -> Result<(), AoC> {
    let mut x = 1 as i64;
    let mut cycles: i64 = 0;
    let mut sum: i64 = 0;
    let mut screen: Vec<char> = vec![' '; 240];

    for line in input.lines() {
        let s: Vec<&str> = line.split_whitespace().collect();

        if s[0] == "noop" {
            cycles += 1;
            sum += check(x, cycles);
            if draw(x, cycles) {
                screen[(cycles - 1) as usize] = '#';
            }
        } else if s[0] == "addx" {
            let pending: i64 = s[1].parse().unwrap();
            cycles += 1;
            sum += check(x, cycles);
            if draw(x, cycles) {
                screen[(cycles - 1) as usize] = '#';
            }

            cycles += 1;
            sum += check(x, cycles);
            if draw(x, cycles) {
                screen[(cycles - 1) as usize] = '#';
            }

            x += pending;
        }
    }

    log(format!("{} {} ", cycles, sum));

    for line in screen.chunks(40) {
        let s: String = line.iter().collect();
        log(format!("{}", s));
    }

    Ok(())
}
