import java.io.File;

// first == win, second == draw, third == points
val rock = Triple<String, String, Int>("C", "A", 1)
val paper = Triple<String, String, Int>("A", "B", 2)
val scissors = Triple<String, String, Int>("B", "C", 3)
val winPoints = 6
val drawPoints = 3

fun main(args : Array<String>) {
    var input = mutableListOf<List<String>>()

    File(args.first()).readLines().forEach {
        input.add(it.split(" "))     
    }

    println("Solution 1: ${solution1(input)}")
    println("Solution 2: ${solution2(input)}")
}

private fun solution1(input: List<List<String>>) :Int {
    var total = 0
    input.forEach {
        when(it.get(1)) {
            "X" -> {
                if (it.get(0).equals(rock.first)) {
                    total += winPoints + rock.third
                } else if (it.get(0).equals(rock.second)) {
                    total += drawPoints + rock.third
                } else {
                    total += rock.third
                }
            }
            "Y" -> {
                if (it.get(0).equals(paper.first)) {
                    total += winPoints + paper.third
                } else if (it.get(0).equals(paper.second)) {
                    total += drawPoints + paper.third
                } else {
                    total += paper.third
                }
            }
            "Z" -> {
                if (it.get(0).equals(scissors.first)) {
                    total += winPoints + scissors.third
                } else if (it.get(0).equals(scissors.second)) {
                    total += drawPoints + scissors.third
                } else {
                    total += scissors.third
                }

            }
        }
    }
    return total
}
    
private fun solution2(input: List<List<String>>) :Int {
    var total = 0
    input.forEach {
        when(it.get(1)) {
            "X" -> { // lose
                when(it.get(0)) {
                    "A" -> {
                        total += scissors.third
                    }
                    "B" -> {
                        total += rock.third
                    }
                    "C" -> {
                        total += paper.third
                    }
                } 
            }
            "Y" -> { // draw
                when(it.get(0)) {
                    "A" -> {
                        total += drawPoints + rock.third
                    }
                    "B" -> {
                        total += drawPoints + paper.third
                    }
                    "C" -> {
                        total += drawPoints + scissors.third
                    }
                } 
            }
            "Z" -> { // win
                when(it.get(0)) {
                    "A" -> {
                        total += winPoints + paper.third
                    }
                    "B" -> {
                        total += winPoints + scissors.third
                    }
                    "C" -> {
                        total += winPoints + rock.third
                    }
                } 
            }
            
        }
    }
    return total
}   
