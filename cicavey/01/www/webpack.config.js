
const HtmlWebpackPlugin = require('html-webpack-plugin');
const CopyPlugin = require("copy-webpack-plugin");
const path = require('path');

module.exports = {
  entry: './bootstrap.js',
  output: {
    path: path.resolve(__dirname, 'dist'),
    filename: 'bootstrap.js',
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: 'index.html',
    }),
    new CopyPlugin({
      patterns: [
        "input.txt"
      ],
    }),
  ],
  mode: "development",
  experiments: {
    asyncWebAssembly: true,
  },
  devServer: {
    open: true
  }
};