from datetime import date
def today():
    return date.today().strftime("%B %d, %Y")

def cursor():
    return '''<span class="cursor"></span>'''