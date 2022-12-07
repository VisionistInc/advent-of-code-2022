type AocErr = ();

#[derive(Debug)]
pub struct Node {
    name: String,
    dir: bool,
    size: u64,
    children: Vec<usize>,
    parent: usize,
}

impl Node {
    pub fn new(name: &str, dir: bool, size: u64, parent: usize) -> Self {
        Node {
            name: name.to_string(),
            dir: dir,
            size: size,
            children: vec![],
            parent: parent,
        }
    }
}

fn calc_size(idx: usize, data: &mut Vec<Node>) -> u64 {
    if !data[idx].dir {
        return data[idx].size;
    }

    let mut size = 0;

    let kids = data[idx].children.to_vec();

    for c in kids.iter() {
        size += calc_size(*c, data);
    }

    data[idx].size = size;

    return size;
}

pub fn run(input: &str, log: fn(String)) -> Result<(), AocErr> {
    // log(format!("{:?}", s));

    let mut data: Vec<Node> = vec![];

    let root = Node::new("/", true, 0, 0);
    data.push(root);

    let mut cur = data.len() - 1;

    for line in input.lines().skip(1) {
        if line.starts_with("$ cd") {
            let s: Vec<&str> = line.split_whitespace().collect();
            let target = s[2];

            if target == ".." {
                cur = data[cur].parent;
            } else {
                for c in data[cur].children.iter() {
                    if data[*c].name == target {
                        // TODO check if dir?
                        cur = *c;
                        break;
                    }
                }
            }

            continue;
        } else if line.starts_with("$ ls") {
            continue;
        }

        // Listing cur dir
        let s: Vec<&str> = line.splitn(2, " ").collect();

        if s[0] == "dir" {
            let name = s[1];
            let dir = Node::new(name, true, 0, cur);

            data.push(dir);

            let new_idx = data.len() - 1;
            data[cur].children.push(new_idx);
        } else {
            let size: u64 = s[0].parse().unwrap();
            let name = s[1];
            let file = Node::new(name, false, size, cur);

            data.push(file);
            let new_idx = data.len() - 1;
            data[cur].children.push(new_idx);
        }

        // log(format!("{}", line));
    }

    // Fix all the sizes
    calc_size(0, &mut data);

    let ans: u64 = data
        .iter()
        .skip(1)
        .filter(|n| n.dir)
        .filter(|n| n.size <= 100000)
        .map(|n| n.size)
        .sum();

    log(format!("{:?}", ans));

    let unused = 70000000 - data[0].size;
    let req = 30000000 - unused;

    let mut candidates: Vec<u64> = data
        .iter()
        .filter(|n| n.dir)
        .filter(|n| n.size >= req)
        .map(|n| n.size)
        .collect();

    candidates.sort();

    log(format!("{:?}", candidates[0]));

    Ok(())
}
