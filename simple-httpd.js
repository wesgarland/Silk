const config = require("./simple-httpd-config");
const fs = require("fs-base");

if (req.uri[req.uri.length - 1] === '/')
    req.uri += "index.html";

print(new Date().toLocaleString() + "\t" + req.uri);

try
{
  let filename = fs.canonical(config.DocumentRoot + req.uri);
  let file = fs.openRaw(filename, { read: true });
  res.write(file.read());
}
catch(e)
{
  res.write("Error processing request: " + e + "<br/>");
  if (e.stack)
    res.write("<hr><pre>" + e.stack + "</pre>");
}

res.write("\n");


