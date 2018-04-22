let component = ReasonReact.statelessComponent("AsyncEntry");
let make = (~item: AsyncModel.todoitem, _children) => {
  ...component,
  render: (_) =>{
    <tr>
      <td>(ReasonReact.stringToElement(string_of_int(item.userId)))</td>
      <td>(ReasonReact.stringToElement(string_of_int(item.id)))</td>
      <td>(ReasonReact.stringToElement(item.title))</td>
      <td>(ReasonReact.stringToElement(item.completed?"Yes":"No"))</td>
    </tr>
  }
};
