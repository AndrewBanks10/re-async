/* 
  Async component state definition and initial values
*/
type state = {
  data: AsyncModel.todos,
  isBusy: bool,
  errorMsg: string
};

let initialState = () => {
  data: [||],
  isBusy: false,
  errorMsg: ""
};

/* 
  Async component reducers
*/
type action =
  | OnGet
  | Busy
  | Loaded(AsyncModel.todos)
  | Error
  | ClearError
  | Clear;

let loadTodos = ({ReasonReact.state, reduce}) => {
  if ( !state.isBusy ) {
    /* Set the busy Indicator */
    reduce(() => Busy, ());
    /* Fetch the todos */
    AsyncModel.fetchTodos(reduce(payload => Loaded(payload)), reduce(() => Error));
  }
};

let reducer = (action, state) =>
  switch action {
    | OnGet =>
        ReasonReact.SideEffects(self =>
          loadTodos(self)
        )
    | Busy => 
        ReasonReact.Update({...state, isBusy: true})
    | Error => 
        ReasonReact.Update({...state, errorMsg: "Error loading data.", isBusy: false})
    | Loaded(data) =>
        ReasonReact.Update({...state, data: data, isBusy: false})
    | ClearError =>
        ReasonReact.Update({...state, errorMsg: ""})
    | Clear =>
        state.isBusy ? ReasonReact.NoUpdate : ReasonReact.Update({...state, data: [||]});
  };

/*
  Async component
*/
let component = ReasonReact.reducerComponent("Async");
let make = (_children) => {
  ...component,
  initialState,
  reducer,
  render: ({state: {data, isBusy, errorMsg}, reduce}) => {
    <div className="app">
      <Loader isBusy />
      <Error errorMsg clearError=(reduce(() => ClearError)) />
      <div className="title">
        (ReasonReact.stringToElement("Async Demo"))
      </div>
      <div className="table-container">
        <table>
          <tbody>
            <tr>
              <th>(ReasonReact.stringToElement("User Id"))</th>
              <th>(ReasonReact.stringToElement("Todo Id"))</th>
              <th>(ReasonReact.stringToElement("Text"))</th>
              <th>(ReasonReact.stringToElement("Completed"))</th>
            </tr>
            (
              data
              |> Array.mapi((index, item) =>
                <AsyncEntry key=(string_of_int(data[index].id)) item />)
              |> ReasonReact.arrayToElement
            )
          </tbody>
        </table>
      </div>
      <button className="ajax-button-container" onClick=(reduce((_) => OnGet))>
        (ReasonReact.stringToElement("Ajax Load"))
      </button>
      <button className="ajax-button-container" onClick=(reduce((_) => Clear))>
        (ReasonReact.stringToElement("Clear"))
      </button>
  </div>
  }
};
