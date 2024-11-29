#pragma once

#include "../sdk.h"
// boost.beast будет использовать std::string_view вместо boost::string_view
#define BOOST_BEAST_USE_STD_STRING_VIEW

#include "listener.h"

namespace http_server{

template <typename RequestHandler>
void ServeHttp(net::io_context& ioc, const tcp::endpoint& endpoint, RequestHandler&& handler) {
  // При помощи decay_t исключим ссылки из типа RequestHandler,
  // чтобы Listener хранил RequestHandler по значению
  using MyListener = Listener<std::decay_t<RequestHandler>>;

  std::make_shared<MyListener>(ioc, endpoint, std::forward<RequestHandler>(handler))->Run();
}


}  
