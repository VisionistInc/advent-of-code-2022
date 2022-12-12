use std::collections::VecDeque;

use euclid::num;
use regex::Regex;
use strum_macros::Display;

#[derive(Debug)]
pub enum AoC {}

#[derive(Debug, PartialEq, Eq, Copy, Clone, Ord, PartialOrd, Hash, Display)]
enum OpKind {
    Add,
    Multiply,
    Square,
}

#[derive(Debug)]
struct Operation {
    operand: usize,
    kind: OpKind,
}

#[derive(Debug)]
struct Monkey {
    items: VecDeque<usize>,
    op: Operation,
    div: usize,
    div_test: usize,
    true_target: usize,
    false_target: usize,
    inspections: u64,
}

pub fn run(input: &str, log: fn(String)) -> Result<(), AoC> {
    let lines: Vec<&str> = input.lines().collect();

    let p1 = true;

    let mut monkeys: Vec<Monkey> = vec![];

    for chunk in lines.chunks(7) {
        let pre_items: Vec<&str> = chunk[1].trim().splitn(3, " ").collect();
        let items: VecDeque<usize> = pre_items[2]
            .split(",")
            .into_iter()
            .map(|i| i.trim().parse().unwrap())
            .collect();

        let pre_op: Vec<&str> = chunk[2].split_whitespace().collect();

        let mut op_kind = match pre_op[4] {
            "*" => OpKind::Multiply,
            _ => OpKind::Add,
        };

        let mut operand = 0;
        if pre_op[5] == "old" {
            op_kind = OpKind::Square;
        } else {
            operand = pre_op[5].parse().unwrap();
        }

        let operation = Operation {
            operand: operand,
            kind: op_kind,
        };

        let div_test: usize = chunk[3].split_whitespace().last().unwrap().parse().unwrap();

        let true_target: usize = chunk[4].split_whitespace().last().unwrap().parse().unwrap();
        let false_target: usize = chunk[5].split_whitespace().last().unwrap().parse().unwrap();

        let monkey = Monkey {
            items: items,
            op: operation,
            div_test,
            div: 3,
            true_target,
            false_target,
            inspections: 0,
        };

        monkeys.push(monkey);
    }

    let num_monkeys = monkeys.len();
    let turns = if p1 { 20_usize } else { 10000_usize } * num_monkeys;

    // I'll admit I cheated here. I spent a DAY fighting with Rust bullshit.
    let lcm: usize = monkeys.iter().map(|m| m.div_test).product();

    for turn in 0..turns {
        let midx = turn % num_monkeys;
        while monkeys[midx].items.len() > 0 {
            let mut item = monkeys[midx].items.pop_back().unwrap();
            monkeys[midx].inspections += 1;
            match monkeys[midx].op.kind {
                OpKind::Add => item += monkeys[midx].op.operand,
                OpKind::Multiply => item *= monkeys[midx].op.operand,
                OpKind::Square => item *= item,
            }
            if p1 {
                item /= monkeys[midx].div;
            } else {
                item = item % lcm;
            }
            let target = if item % monkeys[midx].div_test == 0 {
                monkeys[midx].true_target
            } else {
                monkeys[midx].false_target
            };
            monkeys[target].items.push_back(item);
        }
    }

    monkeys.sort_by(|a, b| b.inspections.cmp(&a.inspections));

    log(format!(
        "{} ",
        monkeys[0].inspections * monkeys[1].inspections
    ));

    Ok(())
}
