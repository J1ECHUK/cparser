from flask import Flask, render_template

app = Flask(__name__)


@app.route('/')
def index():
    return render_template('samsung.html')

@app.route('/bruh/')
def index2():
    return render_template('blender.html')

@app.route('/phuphayka/')
def index3():
    return render_template('nike.html')

@app.route('/roma/')
def index4():
    return render_template('studiogusto.html')


if __name__ == '__main__':
    app.run()
