let component = ReasonReact.statelessComponent("Error");
let make = (~errorMsg, ~clearError, _children) => {
  ...component,
  render: (_) =>{
    if (errorMsg === "") {
      ReasonReact.nullElement
    } else {
      <div className="error-message">
        <div className="error-message-text">(ReasonReact.stringToElement(errorMsg))</div>
        <br />
        <button onClick=((_evt) => clearError())>(ReasonReact.stringToElement("OK"))</button>
      </div>
    }
  }
};