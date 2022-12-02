import java.io.File;

fun main(args : Array<String>) {
    var calLists = mutableListOf<List<Int>>()

    var cals = mutableListOf<Int>()
    File(args.first()).readLines().forEach {
        if (it.isNotBlank()) {
            cals.add(it.toInt())
        } else {
            calLists.add(cals)
            cals = mutableListOf<Int>()
        }
    }

    println("Solution 1: ${solution1(calLists)}")
    println("Solution 2: ${solution2(calLists)}")
}

private fun solution1(input: List<List<Int>>) :Int {
   return input.map{it.sum()}.sorted().last()
}
    
private fun solution2(input: List<List<Int>>) :Int {
   return input.map{it.sum()}.sorted().takeLast(3).sum()
}

