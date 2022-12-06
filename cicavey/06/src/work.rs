use std::collections::HashSet;

type AocErr = ();

pub fn run(input: &str, log: fn(String)) -> Result<(), AocErr> {
    // log(format!("{:?}", s));

    let mut uniq = HashSet::new();
    let mut i = 0;
    for w in input.as_bytes().windows(4) {
        uniq.clear();
        for v in w {
            uniq.insert(*v);
        }
        if uniq.len() == 4 {
            break;
        }
        i += 1;
    }

    log(format!("{:?}", i + 4));

    i = 0;
    for w in input.as_bytes().windows(14) {
        uniq.clear();
        for v in w {
            uniq.insert(*v);
        }
        if uniq.len() == 14 {
            break;
        }
        i += 1;
    }

    log(format!("{:?}", i + 14));

    Ok(())
}
