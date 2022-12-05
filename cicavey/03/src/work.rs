
type AocErr = ();

pub fn score(c: char) -> u64 {
    if c.is_uppercase() {
        (c as u64) - 38
    } else {
        (c as u64) - 96
    }
}

pub fn run(input: &str, log: fn(String)) -> Result<(), AocErr> {

    let mut pri_sum = 0;

    for line in input.lines() {

        let l = line.len();

        let a = &line[0..l/2];
        let b = &line[l/2..];

        for c in a.chars() {
            if b.contains(c) {
                pri_sum += score(c);
                break
            }
        }

        // log(format!("{}\n{}{}",line, a, b));
    }

    log(format!("{}", pri_sum));

    let mut badge_sum = 0;
    let lines: Vec<String> = input.lines().map(str::to_string).collect();
    for chunk in lines.chunks(3) {
        for c in chunk[0].chars() {
            if chunk[1].contains(c) && chunk[2].contains(c) {
                badge_sum += score(c);
                break
            }
        }
    }

    log(format!("{}", badge_sum));


    Ok(())
}
