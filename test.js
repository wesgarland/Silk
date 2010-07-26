/* testing */


/*
function foo() {
    var d = new Date();
    return d.toLocaleString();
}

foo();
*/
res.write('test res.write<br/>\n');
var d = new Date();
var html = '';
html +=d.toLocaleString()+'<br/>\n';
for (var i in req.headers) {
    html += i + ' => ' + req.headers[i] + '<br/>\n';
}
html += global.abc;
res.write(html);
