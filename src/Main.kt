package org.example

class NativeAPI {
    companion object {
        init {
            System.loadLibrary("libnative")
        }
    }
    external fun helloFromCPP(): String
    external fun multiplyMatrices(matA: Matrix, matB: Matrix): Matrix
}

data class Matrix(
    val row: Int,
    val col: Int,
    val values: Array<DoubleArray>
)  {
    constructor(row: Int, col: Int) : this(
        row, col, Array(row) { DoubleArray(col) }
    )
    operator fun get(row: Int, col: Int): Double = values[row][col]
    operator fun set(row: Int, col: Int, value: Double) {
        values[row][col] = value
    }
}

fun KotMultiplyMatrices(matA: Matrix, matB: Matrix): Matrix {
    val result = Matrix(matA.row, matA.col, Array(matA.row) {  DoubleArray(matA.row) })
    for (i in 0 until matA.row) {
        for (j in 0 until matB.col) {
            for (k in 0 until matA.col) {
                result[i, j] += matA[i, k] * matB[k, j]
            }
        }
    }
    return result
}

fun main() {
    val api = NativeAPI()
    println(api.helloFromCPP())

    val size = 500
    val matA = Matrix(size, size, Array(size) { DoubleArray(size) { Math.random() } })
    val matB = Matrix(size, size, Array(size) { DoubleArray(size) { Math.random() } })
    
    val startTime1 = System.nanoTime()
    val result1 = api.multiplyMatrices(matA, matB)
    val elapsedTime1 = (System.nanoTime() - startTime1) / 1_000_000.0
    println("C Library Multiply Matrices (${result1.row}x${result1.col}):")
    println("Result [0][0]: ${result1[0, 0]}")
    println("Time: $elapsedTime1 ms")

    println()

    // Kotlin
    val startTime2 = System.nanoTime()
    val result2 = KotMultiplyMatrices(matA, matB)
    val elapsedTime2 = (System.nanoTime() - startTime2) / 1_000_000.0
    println("Kotlin Multiply Matrices (${result2.row}x${result2.col}):")
    println("Result [0][0]: ${result2[0, 0]}")
    println("Time: $elapsedTime2 ms")
}
