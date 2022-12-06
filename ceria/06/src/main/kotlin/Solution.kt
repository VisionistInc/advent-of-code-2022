import java.io.File;

fun main(args : Array<String>) {
    var input = File(args.first()).readLines().first()

    println("Solution 1: ${solution(input, 4)}")
    println("Solution 2: ${solution(input, 14)}")
}

private fun solution(input: String, markMin: Int) :Int {
    for (i in markMin..input.length) {
        var marker = input.substring(i-markMin, i)
        if (marker.unique()) {
            return i
        }
    }
    return -1
}

fun String.unique(): Boolean = all(hashSetOf<Char>()::add)
