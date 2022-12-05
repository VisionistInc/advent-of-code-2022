import java.io.File;
import java.util.Stack

fun main(args : Array<String>) {

    var input = File(args.first()).readLines()
    var bottomIndex = 0
    var numStacks = 0

    run findBottomsLine@ {
        input.forEachIndexed { index, line ->
            if (!line.contains("[")) {
                bottomIndex = index - 1
                numStacks = line.trim().toList().last().digitToInt()
                return@findBottomsLine
            }
        }
    }

    var listOfStacks = mutableListOf<Stack<Char>>()
    repeat (numStacks) {
        listOfStacks.add(Stack<Char>())
    }

    var listOfLists = mutableListOf<MutableList<Char>>()
    repeat (numStacks) {
        listOfLists.add(mutableListOf<Char>())
    }

    for (i in bottomIndex downTo 0) {
        var line = input.get(i).toList()
        var index = 1
        for (x in 0..numStacks-1) {
            var crate = line.get(index)
            if (!crate.equals(' ')) {
                listOfStacks.get(x).add(crate)
                listOfLists.get(x).add(crate)
            }
            index += 4
        }
    }

    // first = how many, second = from stack, third = to stack
    var listOfMoves = mutableListOf<Triple<Int, Int, Int>>()
    for (y in bottomIndex + 3..input.size - 1) {
        var currLine = input.get(y).split(' ')
        listOfMoves.add(Triple<Int, Int, Int>(currLine.get(1).toInt(), currLine.get(3).toInt(), currLine.get(5).toInt()))
    }    

    println("Solution 1: ${solution1(listOfStacks, listOfMoves)}")
    println("Solution 2: ${solution2(listOfLists, listOfMoves)}")
}

private fun solution1(stacks: List<Stack<Char>>, moves: List<Triple<Int, Int, Int>>) :String {
    moves.forEach { move ->
        repeat(move.first) {
            stacks.get(move.third - 1).push(stacks.get(move.second - 1).pop())
        }
    }  

    return stacks.filter {
        !it.isEmpty()
    }.map { 
        it.last().toString() 
    }.joinToString("")
}
    
private fun solution2(lists: MutableList<MutableList<Char>>, moves: List<Triple<Int, Int, Int>>) :String {
    moves.forEach { move ->
        var fromList = lists.get(move.second -1)
        lists.get(move.third - 1).addAll(fromList.takeLast(move.first))
        lists.set(move.second -1, fromList.dropLast(move.first).toMutableList())
    }

    return lists.filter {
        !it.isEmpty()
    }.map { 
        it.last().toString() 
    }.joinToString("")
}

