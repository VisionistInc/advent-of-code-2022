import java.io.File;

fun main(args : Array<String>) {
    var input = mutableListOf<Pair<ClosedRange<Int>, ClosedRange<Int>>>()
    File(args.first()).readLines().forEach {
        var ranges = it.split(',')
        var firstR = ranges.get(0).split('-')
        var secondR = ranges.get(1).split('-')
        input.add(Pair<ClosedRange<Int>, ClosedRange<Int>>(firstR[0].toInt()..firstR[1].toInt(), secondR[0].toInt()..secondR[1].toInt()))
    }

    println("Solution 1: ${solution1(input)}")
    println("Solution 2: ${solution2(input)}")
}

private fun solution1(input: List<Pair<ClosedRange<Int>, ClosedRange<Int>>>) :Int {
    var total = 0
    input.forEach {
        if (it.first.containedIn(it.second) || it.second.containedIn(it.first)) {
            total++
        }
    }
    return total
}
    
private fun solution2(input: List<Pair<ClosedRange<Int>, ClosedRange<Int>>>) :Int {
    var total = 0
    input.forEach {
        if (it.first.overlaps(it.second) || it.second.overlaps(it.first) ) {
            total++
        }
    }
    return total
}

fun ClosedRange<Int>.containedIn(other: ClosedRange<Int>) =
    start >= other.start && endInclusive <= other.endInclusive

fun ClosedRange<Int>.overlaps(other: ClosedRange<Int>) =
    (start >= other.start && start <= other.endInclusive) || (endInclusive <= other.endInclusive && endInclusive >= other.start)