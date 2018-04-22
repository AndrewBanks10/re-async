let component = ReasonReact.statelessComponent("Loader");
let make = (~isBusy, _children) => {
  ...component,
  render: (_) =>{
    if (isBusy)
      <div className="loader"></div>
    else
      ReasonReact.nullElement
  }
};