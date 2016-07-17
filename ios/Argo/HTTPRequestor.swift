//
//  HTTPRequestor.swift
//  ArgoApp
//
//  Created by Michael Heinzl on 10.07.16.
//
//

import Foundation

public class HTTPRequestor: NSObject, XFHttpRequestor {

	public func executeRequest(request: XFRequest, callback: XFHttpRequestorCallback) {
		let urlRequest = NSMutableURLRequest(URL: NSURL(string: request.url)!)
		let session = NSURLSession.sharedSession()
		urlRequest.HTTPMethod = request.method
		urlRequest.HTTPBody = request.body

		if let header = request.header {
			for (k, v) in header {
				urlRequest.addValue(v, forHTTPHeaderField: k)
			}
		}

		session.dataTaskWithRequest(urlRequest, completionHandler: { data, response, error -> Void in
			if let error = error {
				let e = XFError.init(message: error.localizedDescription)
				callback.receiveError(e)
			} else if let httpResponse = response as? NSHTTPURLResponse {
				let response = XFResponse.init(request: request, header: httpResponse.allHeaderFields as! [String: String], body: data)
				callback.receiveResponse(response)
			} else {
				let e = XFError.init(message: "Something went wrong")
				callback.receiveError(e)
			}
		}).resume()
	}
}
