type AocErr = ();

pub fn run(input: &str, log: fn(String)) -> Result<(), AocErr> {
    const NSTACKS: usize = 9;
    let mut mode = 0;
    let mut stacks: [Vec<char>; NSTACKS] = Default::default();
    for line in input.lines() {
        if line.is_empty() {
            mode = 1;
            continue;
        }

        if mode == 0 {
            let c = line.as_bytes();
            for i in 0..NSTACKS {
                let cur = c[i * 4 + 1];
                if cur == 49 {
                    break;
                }
                if cur == 32 {
                    continue;
                }

                stacks[i].insert(0, cur as char);
            }
        } else {
            let cmd: Vec<&str> = line.split_whitespace().collect();
            let count: u64 = cmd[1].to_string().parse().unwrap();
            let mut from: usize = cmd[3].to_string().parse().unwrap();
            let mut to: usize = cmd[5].to_string().parse().unwrap();

            from -= 1;
            to -= 1;

            // Part one, move one crate at a time
            // for _i in 0..count {
            //     let v = stacks[from].pop().unwrap();
            //     stacks[to].push(v);
            // }

            // Part 2 - pop, reverse, push
            let mut temp = Vec::new();
            for _i in 0..count {
                let v = stacks[from].pop().unwrap();
                temp.push(v);
            }
            // temp.reverse();
            while !temp.is_empty() {
                let v = temp.pop().unwrap();
                stacks[to].push(v);
            }
        }
    }

    let s: String = stacks.iter().filter_map(|s| s.last()).collect();
    log(format!("{:?}", s));

    Ok(())
}
