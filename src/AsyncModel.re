open Json.Decode;
let url = "https://jsonplaceholder.typicode.com/todos";

type todoitem = {
  userId: int,
  id: int,
  title: string,
  completed: bool
};

type todos = array(todoitem);

module Decode = {
  let item = (json) : todoitem => {
    {
      userId: json |> field("userId", int),
      id: json |> field("id", int),
      title: json |> field("title", string),
      completed: json |> field("completed", bool)
    };
  };

  let todosArray = (json) : array(todoitem) =>
    (json |> array(item));
};

let fetchTodos = (callback, fail) =>
  Js.Promise.(
    Fetch.fetch(url)
    |> then_(Fetch.Response.json)
    |> then_(json =>
        json  |> Decode.todosArray
              |>  todosArray => {
                    callback(todosArray);
                    resolve()
                  }
      )
    |> catch((_error) => {
          fail();
          resolve();
       }) 
    |> ignore
  );