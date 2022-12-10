import java.io.File

val strengthCycles = setOf<Int>(20, 60, 100, 140, 180, 220)

fun main(args : Array<String>) {
    // first = cycles, second = x
    var cmdList = mutableListOf<Pair<Int, Int>>()

    File(args.first()).readLines().forEach {        
        when(it.split(' ')[0]) {
            "noop" -> {
                cmdList.add(Pair<Int, Int>(0, 0))
            }
            "addx" -> {
                cmdList.add(Pair<Int, Int>(1, it.split(' ')[1].toInt()))
            }
        }
    }

    println("Solution 1: ${solution1(cmdList)}")
    println("Solution 2:" )
    printScreen(solution2(cmdList))
}

private fun solution1(cmdList: MutableList<Pair<Int, Int>>) :Int {
    var addList = ArrayList(cmdList)
    var signalStrength = 0
    var cycles = 1
    var x = 1   

    while (addList.isNotEmpty()) {
        var cmd = addList.get(0)
        if (cmd.first == 0) {
            x += cmd.second
            addList.removeAt(0)
        } else {
            var newCmd = cmd.copy(first = cmd.first - 1)
            addList.set(0, newCmd)
        }

        cycles++

        if (strengthCycles.contains(cycles)) {
            signalStrength += (x * cycles)
        }

    }

    return signalStrength
}

private fun solution2(cmdList: MutableList<Pair<Int, Int>>) :List<String> {
    var screen = mutableListOf<String>()
    var currScreenRow = "#"
    var lineCount = 0
    var addList = ArrayList(cmdList)
    var spritePos = 0..2
    var cycles = 1
    var x = 1   

    while (addList.isNotEmpty()) {
        var cmd = addList.get(0)
        if (cmd.first == 0) {
            x += cmd.second
            var pos = (lineCount * 40) + x
            spritePos = pos - 1..pos + 1
            addList.removeAt(0)
        } else {
            var newCmd = cmd.copy(first = cmd.first - 1)
            addList.set(0, newCmd)
        }

        if (spritePos.contains(cycles)) {
            currScreenRow += '#'
        } else {
            currScreenRow += "."
        }

        if (currScreenRow.length % 40 == 0) {
            screen.add(currScreenRow)
            currScreenRow = ""
            lineCount++
        }

        cycles++
    }

    return screen
}

fun printScreen(screen: List<String>) {
    println()
    screen.forEach{
        println(it)
    }
    println()
}