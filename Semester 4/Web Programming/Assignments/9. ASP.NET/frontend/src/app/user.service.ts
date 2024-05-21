import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders, HttpParams } from '@angular/common/http';
import { Observable, of } from 'rxjs';
import { catchError } from 'rxjs/operators';
import { User } from './user';

@Injectable({
  providedIn: 'root'
})
export class UserService {
  private backendUrl = 'https://localhost:8000'; 

  constructor(private http: HttpClient) {}

  fetchUsers(role?: string, name?: string): Observable<User[]> {
    let params = new HttpParams();
    if (role) {
      params = params.set('role', role);
    }
    if (name) {
      params = params.set('name', name);
    }
    const UsersPath = this.backendUrl + '/users';
    return this.http.get<User[]>(UsersPath, { params }).pipe(
      catchError(this.handleError<User[]>('fetchUsers', []))
    );
  }

  deleteUser(userId: string): Observable<any> {
    console.log('Deleting user with id:', userId);
    const deletePath = `${this.backendUrl}/delete?userID=${userId}`

    console.log('Deleting user with id:', userId)

    return this.http.delete(deletePath).pipe(
      catchError(this.handleError<any>('deleteUser'))
    );
  }

  addUser(userData: any): Observable<any> {
    const addPath = this.backendUrl + "/add";
    const params = new HttpParams({fromObject: userData});

    const httpOptions = {
      headers: new HttpHeaders({ 
        'Content-Type': 'application/x-www-form-urlencoded' })
    };

    console.log('Adding user with data:', userData);

    return this.http.post(addPath, params, httpOptions).pipe(
      catchError(this.handleError<any>('addUser')));
  }

  updateUser(userId:string, userData:any): Observable<any> {
    const updatePath = this.backendUrl + "/update?userID=" + userId;
    const params = new HttpParams({fromObject: userData});

    const httpOptions = {
      headers: new HttpHeaders({ 
        'Content-Type': 'application/x-www-form-urlencoded'
      })
    };
  
    console.log(userId, userData);
    return this.http.put(updatePath, params, httpOptions).pipe(
      catchError(this.handleError<any>('updateUser')));
  }

  getUserData(userId: string): Observable<any> {
    const userPath = `${this.backendUrl}/user?userID=${userId}`;
    return this.http.get<User>(userPath).pipe(
      catchError(this.handleError<User>('getUserData')));
  }

  login(loginData:any): Observable<any> {
    console.log('Logging in with data:', loginData);
    const loginPath = this.backendUrl + '/login';
    const params = new HttpParams({fromObject: loginData});

    const httpOptions = {
      headers: new HttpHeaders({ 
        'Content-Type': 'application/x-www-form-urlencoded' })
    };

    return this.http.post(loginPath, params, httpOptions).pipe(
      catchError(this.handleError<any>('login')));
  }

  private handleError<T>(operation = 'operation', result?: T): (error: any) => Observable<T> {
    return (error: any): Observable<T> => {
      console.error(error);
      return of(result as T);
    };
  }
}
