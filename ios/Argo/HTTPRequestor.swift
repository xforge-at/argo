//
//  HTTPRequestor.swift
//  ArgoApp
//
//  Created by Michael Heinzl on 10.07.16.
//
//

import Foundation

open class HTTPRequestor: NSObject, XFHttpRequestor {

	open func execute(_ request: XFRequest, callback: XFHttpRequestorCallback) {
		let urlRequest = NSMutableURLRequest(url: URL(string: request.url)!)
		let session = URLSession.shared
		urlRequest.httpMethod = request.method
		urlRequest.httpBody = request.body

		if let header = request.header {
			for (k, v) in header {
				urlRequest.addValue(v, forHTTPHeaderField: k)
			}
		}

		session.dataTask(with: urlRequest, completionHandler: { data, response, error -> Void in
			if let error = error {
				let e = XFError.init(code: 0, message: error.localizedDescription)
				callback.receiveError(e)
			} else if let httpResponse = response as? HTTPURLResponse {
				let response = XFResponse.init(request: request, statusCode: Int32(httpResponse.statusCode), header: httpResponse.allHeaderFields as! [String: String], body: data)
				callback.receive(response)
			} else {
				let e = XFError.init(code: 0, message: "Something went wrong")
				callback.receiveError(e)
			}
		}).resume()
	}
}
