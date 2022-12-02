use std::str::FromStr;
use strum_macros::Display;

#[derive(Copy, Clone, Debug, Eq, PartialEq, Display)]
pub enum Hand {
    Rock = 1,
    Paper = 2,
    Scissors = 3,
}

#[derive(Copy, Clone, Debug, Eq, PartialEq, Display)]
pub enum HandResult {
    Win = 6,
    Lose = 0,
    Draw = 3,
}

pub trait Beats {
    fn beats(&self) -> Hand;
}

impl Beats for Hand {
    fn beats(&self) -> Hand {
        // match is exhaustive, so every enum variant must be covered
        match *self {
            Hand::Rock => Hand::Scissors,
            Hand::Paper => Hand::Rock,
            Hand::Scissors => Hand::Paper,
        }
    }
}

fn required(op_hand: Hand, hand_result: HandResult) -> Hand {
    match hand_result {
        HandResult::Draw => op_hand,
        HandResult::Win => match op_hand {
            Hand::Rock => Hand::Paper,
            Hand::Paper => Hand::Scissors,
            Hand::Scissors => Hand::Rock,
        },
        HandResult::Lose => match op_hand {
            Hand::Rock => Hand::Scissors,
            Hand::Paper => Hand::Rock,
            Hand::Scissors => Hand::Paper,
        },
    }
}

type AocErr = ();

impl FromStr for Hand {
    type Err = ();

    fn from_str(input: &str) -> Result<Hand, AocErr> {
        match input {
            "A" | "X" => Ok(Hand::Rock),
            "B" | "Y" => Ok(Hand::Paper),
            "C" | "Z" => Ok(Hand::Scissors),
            _ => Err(()),
        }
    }
}

impl FromStr for HandResult {
    type Err = ();

    fn from_str(input: &str) -> Result<HandResult, AocErr> {
        match input {
            "X" => Ok(HandResult::Lose),
            "Y" => Ok(HandResult::Draw),
            "Z" => Ok(HandResult::Win),
            _ => Err(()),
        }
    }
}

pub fn run(input: &str, log: fn(String)) -> Result<(), AocErr> {
    let mut total_score = 0;
    let mut total_score2 = 0;
    for line in input.lines() {
        let pairs: Vec<String> = line.split_whitespace().map(str::to_string).collect();

        let op_hand = Hand::from_str(&pairs[0])?;

        // Pretend second col is my hand
        let my_hand = Hand::from_str(&pairs[1])?;
        let hand_result = if my_hand == op_hand {
            HandResult::Draw
        } else if my_hand.beats() == op_hand {
            HandResult::Win
        } else {
            HandResult::Lose
        };
        total_score += my_hand as u64 + hand_result as u64;

        // Pretend second col is outcome
        let desired_result = HandResult::from_str(&pairs[1])?;
        let desired_hand = required(op_hand, desired_result);
        total_score2 += desired_hand as u64 + desired_result as u64;
    }

    log(format!("{} {}", total_score, total_score2)); // 12794

    Ok(())
}
