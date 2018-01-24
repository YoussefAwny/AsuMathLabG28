string  Matrix::first_operation(string s /*,opened_parentheses[],closed_parentheses[]*/)
{
	int opened_parenthese_location;
		//    if(opened_parentheses.length() != closed_parentheses.length() )
		//      {
		//    throw("please enter same number of opened and closed brackets in the matrix. \n ");
		//  return (string) s;
		//}
	for (int i = 0; i < s.length() + 1; i++)
	{
		if (s.substr(i, 1) == "(")
			opened_parenthese_location = i;
		else if (s.substr(i, 1) == ")")
			return s.substr((opened_parenthese_location + 1), (i - (opened_parenthese_location + 1)));
		else
			continue;
	}

}
