/**
 * @file test_httplib_server.cc
 * @author your name (you@domain.com)
 * @brief httplib server unit test
 * @version 0.1
 * @date 2023-08-24
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <string>
#include <iostream>
#include <fstream>

#include "httplib.h"

using namespace std;
using namespace httplib;

int test_httplib_server_hi()
{
    Server svr;

    svr.Get("/hi", [](const Request &, Response &res)
            { res.set_content("Hello world", "text/plain"); });

    svr.listen("0.0.0.0", 29001);
}

const char *html = R"(
<form id="formElem">
  <input type="file" name="image_file" accept="image/*">
  <input type="file" name="text_file" accept="text/*">
  <input type="submit">
</form>
<script>
  formElem.onsubmit = async (e) => {
    e.preventDefault();
    let res = await fetch('/post', {
      method: 'POST',
      body: new FormData(formElem)
    });
    console.log(await res.text());
  };
</script>
)";

int test_httplib_server_upload()
{
    Server svr;

    svr.Get("/", [](const Request & /*req*/, Response &res)
            { res.set_content(html, "text/html"); });

    svr.Post("/post", [](const Request &req, Response &res)
             {
    auto image_file = req.get_file_value("image_file");
    auto text_file = req.get_file_value("text_file");

    cout << "image file length: " << image_file.content.length() << endl
         << "image file name: " << image_file.filename << endl
         << "text file length: " << text_file.content.length() << endl
         << "text file name: " << text_file.filename << endl;

    {
      ofstream ofs(image_file.filename, ios::binary);
      ofs << image_file.content;
    }
    {
      ofstream ofs(text_file.filename);
      ofs << text_file.content;
    }

    res.set_content("done", "text/plain"); });

    svr.listen("localhost", 1234);
}

int main()
{
    test_httplib_server_upload();
}