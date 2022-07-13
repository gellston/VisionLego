#pragma once


namespace vl {

	class ihandle {
	public:
		virtual ~ihandle() {};
	};

	using poiner_ihandle = std::shared_ptr<vl::ihandle>;
}